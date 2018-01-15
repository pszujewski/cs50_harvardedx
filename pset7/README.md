### Lecture 6

More Python Features, The Flask Framework, MVC Pattern, and Introduction to SQL

**The MVC pattern or framework**

Controllers: The business logic goes here, the function calls that do things.
View: templates that actually render information
Model: Databases, how you save, search, delete, etc. The Model also describes the schema for the database, which refers to the design of the tables and rows, as well as how data is stored in the database.

**Basic Flask App setup**

```python
from flask import Flask, render_template, request

# where __name__ is a global ENV variable in a python process
# it is a reference to the current file

app = Flask(__name__)

# syntax for a decorator (see Flask docs)
# tells server to call function tied to that route

@app.route("/)
     def index():
          return render_template("index.html")

@app.route("/register" methods=["POST"])
     def register():
          if request.form["name"] == "" or request.form["dorm"] == "":
               return render_template("failure.html")
          return render_template("success.html")
```

Flask uses a python generated templating language called Jinja to create the html template. Templates go in a 'templates' directory at the root of the project. The above is an example of "controller code"

A "backend" is a web server that responds to HTTP requests over TCP ports.

**Writing to a CSV file in python**

The example is done in the context of a Flask route that takes in data on "request" object

```python
import csv

file = open("registrants.csv", "a") # a is for appending to a file, "w" would override each time
writer = csv.writer(file)
writer.writerow(request.form["name"], request.form["dorm"])
file.close()
```

Just writing to files is not efficient and does not scale well. Thus was born SQL. MySql, postgreSQL actually run servers that listen for requests. SQLite does not require this.
Data types are defined in SQL for performance reasons.
Primary key => the field whose values uniquely identify records in a table. The primary key has special status and is always unique.
Index => Allows you to have the database give you better performance than linear search. If you know for example that you are going to be searching by zip code or email, you can tell the database in advance that it should 'index' records by that field. In effect, the db will index, or (sort of) sort, records in advance. Only use this if you are going to search by that field, however.
UNIQUE => Allows you to identify a field as unique. So if you say that email is unique, then SQL won't allow you to create another record with the same email

**Basic SQL CRUD operations**

```
INSERT INTO registrants(name, dorm)
     VALUES('Peter', 'Currier');
```

To get a result set, you can select certain records and specify the fields you want to see.

```
SELECT * from registrants
```

To Create a new SQL table

```
CREATE TABLE 'registrants'
     ('id' INTEGER PRIMARY KEY, 'name' TEXT, 'dorm' TEXT)
```

Update!

```
UPDATE registrants SET name = 'David' WHERE id = 2

DELETE FROM registrants where id = 1
```

SQL also comes with built-in functions: date, datetime, etc. Finally, Joins in SQL allow you to combine data from 2 or more tables at will. The following is an example that 'joins' the users table to the zipcodes table where each users' id field equals the zipcode id

```
SELECT * FROM users JOIN zipcodes ON users.zipcode = zipcodes.id
```

Type `.tables` in sqlite to show all tables available in the database.

`flask_sqlalchemy` is a python package for using sql in a python flask application.

