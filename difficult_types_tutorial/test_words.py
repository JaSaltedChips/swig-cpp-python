import wordstore

store = wordstore.WordStore()
store.add("alpha")
store.add("beta")
store.add("gamma")

print("Count:", store.count())
print("Join:", store.join(" | "))

print("Words (copy):", store.words())
print("Words (ref):", store.words_ref())

print("Total length:", wordstore.total_length(["one", "two", "three"]))
