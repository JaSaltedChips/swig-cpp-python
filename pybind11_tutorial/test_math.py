import rechner_pybind as rp

calc = rp.Calculator()

print("Add:", calc.add(5, 3))
print("Multiply:", calc.multiply(7, 4))
print("Power:", calc.power(2, 10))
print("Square Root:", calc.squareRoot(16))
