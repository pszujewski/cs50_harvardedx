from cs50 import SQL
from flask import Flask, render_template, redirect, request, url_for

app = Flask(__name__)

# tell cs50 library to use sqlite and open a db file called froshims2

db = SQL("sqlite:///froshims2.db")

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/register", methods=["POST"])
def register():
    if request.form["name"] == "" or request.form["dorm"] == "":
        return render_template("failure.html")
    db.execute("INSERT INTO registrants (name, dorm) VALUES(:name, :dorm)",
        name=request.form["name"], dorm=request.form["dorm"]) # : is often a placeholder convention that says 'this is a variable'
    return render_template("success.html")