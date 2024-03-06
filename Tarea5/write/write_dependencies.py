import yaml
from jinja2 import Environment, FileSystemLoader

with open("dependencies.yaml", "r") as f:
    yp = yaml.load(f, Loader=yaml.FullLoader)

environment = Environment(loader=FileSystemLoader("templates/"))

results_filename_1 = "CMakeLists.txt"
results_template_1 = environment.get_template("CMakeLists.txt")
results_filename_2 = "package.xml"
results_template_2 = environment.get_template("package.xml")

context = {
    "project_name": yp['project_name'],
    "packages": yp['packages'],
    "executables": yp['executables'],
}

with open(results_filename_1, mode="w", encoding="utf-8") as results:
    results.write(results_template_1.render(context))
    print(f"... wrote {results_filename_1}")
with open(results_filename_2, mode="w", encoding="utf-8") as results:
    results.write(results_template_2.render(context))
    print(f"... wrote {results_filename_2}")
