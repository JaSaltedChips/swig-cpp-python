import typemaps_demo as td

p1 = {"x": 2, "y": 5}
p2 = {"x": -1, "y": 4}

print("make_point:", td.make_point(3, 7))
print("add_points:", td.add_points(p1, p2))
print("scale_point:", td.scale_point(p1, 3))
print("manhattan_length:", td.manhattan_length(p2))
