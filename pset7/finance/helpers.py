import csv
import urllib.request

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Renders message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/0.12/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # reject symbol if it starts with caret
    if symbol.startswith("^"):
        return None

    # reject symbol if it contains comma
    if "," in symbol:
        return None

    # query Yahoo for quote
    # http://stackoverflow.com/a/21351911
    try:

        # GET CSV
        url = f"http://download.finance.yahoo.com/d/quotes.csv?f=snl1&s={symbol}"
        webpage = urllib.request.urlopen(url)

        # read CSV
        datareader = csv.reader(webpage.read().decode("utf-8").splitlines())

        # parse first row
        row = next(datareader)

        # ensure stock exists
        try:
            price = float(row[2])
        except:
            return None

        # return stock's name (as a str), price (as a float), and (uppercased) symbol (as a str)
        return {
            "name": row[1],
            "price": price,
            "symbol": row[0].upper()
        }

    except:
        pass

    # query Alpha Vantage for quote instead
    # https://www.alphavantage.co/documentation/
    try:

        # GET CSV
        url = f"https://www.alphavantage.co/query?apikey=NAJXWIA8D6VN6A3K&datatype=csv&function=TIME_SERIES_INTRADAY&interval=1min&symbol={symbol}"
        webpage = urllib.request.urlopen(url)

        # parse CSV
        datareader = csv.reader(webpage.read().decode("utf-8").splitlines())

        # ignore first row
        next(datareader)

        # parse second row
        row = next(datareader)

        # ensure stock exists
        try:
            price = float(row[4])
        except:
            return None

        # return stock's name (as a str), price (as a float), and (uppercased) symbol (as a str)
        return {
            "name": symbol.upper(), # for backward compatibility with Yahoo
            "price": price,
            "symbol": symbol.upper()
        }

    except:
        return None


def usd(value):
    """Formats value as USD."""
    return f"${value:,.2f}"

def addSharesToTransaction(shares_by_company, transaction):
    print("Adding shares to transaction now.")
    for i in range(len(shares_by_company)):
        c = shares_by_company[i]
        if c["symbol"] == transaction["symbol"]:
            updated_num_shares = c["num_shares"] + transaction["shares_bought"]
            #updated_total_value = c["current_price"] * float(updated_num_shares)
            c["num_shares"] = updated_num_shares
            #c["total_value"] = updated_total_value
    print("Finished adding shares")

def getTotalCashValueOfAllShares(shares_by_company):
    # add up the total value of shares in each company
    total = 0.0
    for i in range(len(shares_by_company)):
        total += shares_by_company[i]["total_value"]
    return total

def getCompanyAndTotalPrice(request):
    """handles validating form data for buy and sell"""

    symbol = request.form.get("stock_symbol")
    if not symbol or symbol == "":
        return apology("must provide a stock symbol");

    num_shares = float(request.form.get("num_shares"))

    if not num_shares or num_shares == 0:
        return apology("must provide valid number of shares")

    # query yahoo api to get the current price of one share for the company
    company = lookup(symbol.strip())

    if not company:
        return apology("unable to complete request.")

    totalPrice = company["price"] * num_shares;

    return {
        "company": company,
        "num_shares": num_shares,
        "totalPrice": totalPrice
    }
