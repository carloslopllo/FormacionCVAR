from jinja2 import Environment, FileSystemLoader

deque = ["data1_dq", "data2_dq"]
subscribers = [
    {"name":"sub_1","topic":'"data1"',"callback":"callback_1","deque":deque[0]},
    {"name":"sub_2","topic":'"data2"',"callback":"callback_2","deque":deque[1]},
]
publishers = [
    {"name":"pub_1","topic":'"sum"'},
    {"name":"pub_2","topic":'"minus"'},
]
rest = [
    {"name":"n1","deque":deque[0],"type":"std::deque<int>"},
    {"name":"n2","deque":deque[1],"type":"std::deque<int>"},
]
environment = Environment(loader=FileSystemLoader("templates/"))
results_filename = "main.cpp"
results_template = environment.get_template("main.cpp")
context = {
    "name": '"main"',
    "type": "Int32",
    "subscribers": subscribers,
    "publishers": publishers,
    "autos": ["sum","minus"],
    "rest": rest,
    "deque": deque,
}
with open(results_filename, mode="w", encoding="utf-8") as results:
    results.write(results_template.render(context))
    print(f"... wrote {results_filename}")
