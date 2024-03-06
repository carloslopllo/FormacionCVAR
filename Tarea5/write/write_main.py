import yaml
from jinja2 import Environment, FileSystemLoader

with open("main.yaml", "r") as f:
    yp = yaml.load(f, Loader=yaml.FullLoader)
environment = Environment(loader=FileSystemLoader("templates/"))
results_filename = "main.cpp"
results_template = environment.get_template("main.cpp")
context = {
    "name": yp['name'],
    "type": yp['type'],
    "subscribers": yp['subscribers'],
    "publishers": yp['publishers'],
    "autos": yp['autos'],
    "class_name": yp['class_name'],
    "includes": yp['includes'],
}
with open(results_filename, mode="w", encoding="utf-8") as results:
    results.write(results_template.render(context))
    print(f"... wrote {results_filename}")
