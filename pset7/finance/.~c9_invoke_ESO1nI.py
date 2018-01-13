from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance-02.db")

def getAllTransactions():
    all_sold = db.execute("SELECT symbol, SUM(shares_sold) AS shares_sold FROM sales WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
    all_bought = db.execute("SELECT symbol, SUM(shares_bought) AS shares_bought FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
    return {
        "all_sold": all_sold,
        "all_bought": all_bought
    }

def getUserByUsername(request):
    # ensure username was submitted
    if not request.form.get("username"):
        return apology("must provide username")

    # ensure password was submitted
    elif not request.form.get("password"):
        return apology("must provide password")

    # query database for username
    rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

    # ensure username exists and password is correct
    if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
        return apology("invalid username and/or password")

    # return the validated user record
    return rows[0]

@app.route("/")
@login_required
def index():

    holdings = []

    t = getAllTransactions()
    all_sold = t["all_sold"]
    all_bought = t["all_bought"]

    for i in range(len(all_bought)):
        curr_buy = all_bought[i]
        holding = {
            "symbol": curr_buy["symbol"],
            "num_shares": curr_buy["shares_bought"],
        }
        for j in range(len(all_sold)):
            if curr_buy["symbol"] == all_sold[j]["symbol"]:
                holding["num_shares"] -= all_sold[j]["shares_sold"]
                break
        holdings.append(holding)

    # get the user's cash holdings
    user = db.execute("SELECT id, username, cash FROM users WHERE id = :user_id", user_id=session["user_id"])

    return render_template("index.html", holdings=holdings, cash_balance=usd(user[0]["cash"]))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "GET":
        return render_template("buy.html")

    # otherwise its a post method
    r = getCompanyAndTotalPrice(request)

    # get the user from the db
    user = db.execute("SELECT id, username, cash FROM users WHERE id = :user_id", user_id=session["user_id"])

    hasEnoughCash = user[0]["cash"] > r["totalPrice"]
    if not hasEnoughCash:
        return apology("You must have more cash to complete this transaction")

    # user has enough cash, so subtract the transaction amount from the user's cash
    newCashAmt = user[0]["cash"] - r["totalPrice"]

    # update user record with new cash amount in db
    db.execute("UPDATE users SET cash = :newCashAmt WHERE id = :user_id", newCashAmt=newCashAmt, user_id=session["user_id"])

    # Insert a new transaction for the current user based on number of shares they want to 'buy'
    db.execute("INSERT into transactions(symbol, purchase_price, shares_bought, user_id) VALUES(:symbol, :price, :shares, :u_id)", symbol=r["company"]["symbol"], price=r["company"]["price"], shares=r["num_shares"], u_id=session["user_id"])

    # For buy, after completing buy redirect to index so user can see
    # which stocks they own, the numbers of shares owned, and their total cash balance

    return redirect(url_for("index"))

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    all_sold = db.execute("SELECT symbol, shares_sold, sale_price, register_date FROM sales WHERE user_id = :user_id", user_id=session["user_id"])
    all_bought = db.execute("SELECT symbol, shares_bought, purchase_price, register_date FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])

    return render_template("history.html", purchases=all_bought, sales=all_sold)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        user = getUserByUsername(request)

        # remember which user has logged in
        session["user_id"] = user["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    # otherwise, it's a post
    symbol = request.form.get("stock_symbol")
    if not symbol or symbol == "":
        return apology("must provide a stock symbol");

    company = lookup(symbol.strip())

    return render_template("quoted.html", company=company)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    if request.method == "GET":
        return render_template("register.html")

    elif request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure confirm_pw was submitted
        elif not request.form.get("confirm_pw"):
            return apology("must provide confirmation password")

        # ensure confirm_pw and password match
        elif not request.form.get("confirm_pw") == request.form.get("password"):
            return apology("passwords must match")

        # password and usernames are valid, hash the password
        pw_hash = pwd_context.hash(request.form.get("password"))

        # insert the new user into the db
        db.execute("INSERT INTO users(username, hash) VALUES(:username, :pw_hash)", username=request.form.get("username"), pw_hash=pw_hash)

        return render_template("login.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""

    if request.method == "GET":
        return render_template("sell.html")

     # otherwise its a post method
    r = getCompanyAndTotalPrice(request)

    # get the user from the db
    user = db.execute("SELECT id, username, cash FROM users WHERE id = :user_id", user_id=session["user_id"])

    # Add the total price of selling the shares
    newCashAmt = user[0]["cash"] + r["totalPrice"]

    # update user record with new cash amount in db
    db.execute("UPDATE users SET cash = :newCashAmt WHERE id = :user_id", newCashAmt=newCashAmt, user_id=session["user_id"])

     # Insert a new sale for the current user based on number of shares they want to 'sell'
    db.execute("INSERT into sales(symbol, sale_price, shares_sold, user_id) VALUES(:symbol, :price, :shares, :u_id)", symbol=r["company"]["symbol"], price=r["company"]["price"], shares=r["num_shares"], u_id=session["user_id"])

    return redirect(url_for("index"))

@app.route("/account", methods=["GET", "POST"])
@login_required
def changePassword():

    if request.method == "GET":
        return render_template("change_password.html")

    # user should have to revalidate their creds in order to change their pw
    user = getUserByUsername(request)

    # ensure new password was submitted
    if not request.form.get("new_pw"):
        return apology("must provide a new password password")

    # ensure it was confirmed
    elif not request.form.get("confirm_new_pw"):
        return apology("must provide a confirmation password")

    # ensure they match
    elif not request.form.get("new_pw") == request.form.get("confirm_new_pw"):
        return apology("new password and confirm password values must match")

    # new password request is valid, so hash the new password
    new_pw_hash = pwd_context.hash(request.form.get("new_pw"))

     # update user record with their new password hash
    db.execute("UPDATE users SET hash = :new_pw_hash WHERE id = :user_id", new_pw_hash=new_pw_hash, user_id=session["user_id"])

    return redirect(url_for("index"))