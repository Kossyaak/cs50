import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

def provided(field):
    if not request.form.get(field):
        return apology(f"must provide {field}", 400)



@app.route("/artmoney", methods=["GET", "POST"])
@login_required
def artmoney():
    if request.method == "POST":
        db.execute("UPDATE users SET cash = cash + :amount WHERE id = :idd", amount = request.form.get("cash"), idd = session["user_id"])
        flash("Easy money!)")
        return redirect("/")
    else:
        return render_template("artmoney.html")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, SUM(shares) as totalShares FROM transactions WHERE user_id = :idd GROUP BY symbol HAVING totalShares > 0", idd = session["user_id"])
    holdings = []
    total = 0
    for row in rows:
        stock = lookup(row["symbol"])
        holdings.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": row["totalShares"],
            "price": usd(stock["price"]),
            "total": usd(stock["price"] * row["totalShares"])
        })
        total =  stock["price"] * row["totalShares"]
    user_balance = db.execute("SELECT cash FROM users WHERE id = :idd", idd = session["user_id"])
    cash = user_balance[0]["cash"]
    total += cash
    return render_template("index.html", holdings=holdings, cash = usd(cash), total = usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares")
        symbol = request.form.get("symbol").upper()
        checks = provided("symbol") or provided("shares")
        if checks is not None:
            return checks
        elif not shares.isdigit():
            return apology("Number of shares must be integer", 400)
        elif int(shares) < 1:
            return apology("Number of shares must be > 0", 400)
        stock = lookup(symbol)
        if stock is None:
            return apology("Wrong symbol", 400)
        cash = db.execute("SELECT cash FROM users WHERE id = :idd", idd = session["user_id"])
        shares_int = int(shares)
        user_cash = cash[0]["cash"]
        new_user_cash = user_cash - shares_int * stock['price']
        if new_user_cash < 0:
            return apology("Can't buy a shares, not enough money", 403)
        else:
            db.execute("UPDATE users SET cash= :updated_cash WHERE id = :idd", updated_cash = new_user_cash, idd = session["user_id"])
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
            user_id=session["user_id"],
            symbol=stock["symbol"],
            shares=shares_int,
            price=stock["price"]
            )
            flash("Deal")
            return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    all_trans = db.execute("SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = :idd", idd = session["user_id"])
    for i in range(len(all_trans)):
        all_trans[i]["price"] = usd(all_trans[i]["price"])
    return render_template("history.html", all_trans = all_trans)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        checks = provided("username") or provided("password")
        if checks is not None:
            return checks

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        check = provided("symbol")
        if check is not None:
           return check
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if stock is None:
            return apology("Wrong symbol", 400)
        else:

            return render_template("quoted.html", stockname = {
            'name': stock['name'],
            'symbol': stock['symbol'],
            'price': usd(stock['price'])} )
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")
    if request.method == "POST":
        checks = provided("username") or provided("password") or provided("confirmation")
        if checks is not None:
            return checks
        elif not password == confirmation:
            return apology("passwords must match", 400)
        try:
            user = db.execute("INSERT INTO users(username, hash) VALUES (:username, :hashh)", username = username, hashh = generate_password_hash(password))
        except:
             return apology("This username is already taken", 400)
        if user is None:
            return apology("Failed to register user", 403)

        session["user_id"] = user
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares")
        symbol = request.form.get("symbol").upper()
        checks = provided("symbol") or provided("shares")
        shares_int = int(shares)
        if checks is not None:
            return checks
        elif not shares.isdigit():
            return apology("Number of shares must be integer", 403)
        elif int(shares) < 1:
            return apology("Number of shares must be > 0", 403)
        stock = lookup(symbol)
        if stock is None:
            return apology("Wrong symbol", 400)
        rows = db.execute("SELECT symbol, SUM(shares) as totalShares FROM transactions WHERE user_id = :idd GROUP BY symbol HAVING totalShares > 0", idd = session["user_id"])
        for row in rows:
            if row["symbol"] == symbol:
                if shares_int > row["totalShares"]:
                    return apology("too many shares")
        cash = db.execute("SELECT cash FROM users WHERE id = :idd", idd = session["user_id"])
        user_cash = cash[0]["cash"]
        new_user_cash = user_cash + shares_int * stock['price']

        db.execute("UPDATE users SET cash= :updated_cash WHERE id = :idd", updated_cash = new_user_cash, idd = session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
        user_id=session["user_id"],
        symbol=stock["symbol"],
        shares= -1 *shares_int,
        price=stock["price"]
        )
        flash("Deal")
        return redirect("/")
    else:
        rows = db.execute("SELECT symbol FROM transactions WHERE user_id = :idd GROUP BY symbol HAVING SUM(shares) > 0", idd = session["user_id"])
        return render_template("sell.html", symbols = [ row["symbol"] for row in rows])
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
