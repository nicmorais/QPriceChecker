
# QPriceChecker
A price checker made with Qt, which can run on a Raspberry Pi, PocketCHIP, Orange Pi and other SBCs.

![Screenshot](https://raw.githubusercontent.com/nicmorais/QPriceChecker/main/screenshot.png)

### Setting up a server
The server must respond at the endpoint "/product" with barcode as parameter (eg. " /product?barcode=9999") providing a JSON object containing the product's name and it's price:
```javascript
{ "name": "Product Name", "price": 5.9 }
```
You can setup a simple server with [Flask](https://flask.palletsprojects.com/) with the following code:
```python
from flask import Flask, json, request, Response

api = Flask(__name__)
def find_product(barcode):
  with open('products.txt', 'r', encoding = "UTF-8") as f:
    lines = f.readlines()
    for line in lines:
      if line[0:len(barcode)] == barcode:
        lineList = line.split('|')
        nameAndPrice = {'name': lineList[1], 'price': float(lineList[2])}
        return json.dumps(nameAndPrice, indent = 4)
        break
  return Response("404",status = 404)

@api.route('/', methods=['GET'])
def index_page():
  return 'Running'

@api.route('/product', methods=['GET'])
def get_product():
  barcode = request.args.get('barcode')
  return find_product(barcode)

if __name__ == '__main__':
    api.run() 
```
In this case, you need a text files containing all products and their prices (products.txt), like this:
```
1246975662122|Product A|9.20|
8963638439391|Product B|5.20|
1328713290939|Product C|2.60|
```

### Building and Running
**QMake:**
```bash
cd QPriceChecker
qmake QPriceChecker.pro
make
./QPriceChecker
```
