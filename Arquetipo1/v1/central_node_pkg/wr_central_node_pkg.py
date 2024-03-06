import yaml
from jinja2 import Environment, FileSystemLoader

with open("manifest.yaml", "r") as f:
	yp = yaml.load(f, Loader=yaml.FullLoader)

environment = Environment(loader=FileSystemLoader("templates/"))

central_node = "src/central_node.cpp"
central_node_template = environment.get_template("t_central_node.cpp")

CMakeLists = "CMakeLists.txt"
CMakeLists_template = environment.get_template("t_CMakeLists.txt")

package = "package.xml"
package_template = environment.get_template("t_package.xml")

context = {
	# t_central_node.cpp
	"includes": yp["includes"],
	"class_name": yp["class_name"],
	"node_name": yp["node_name"],
	"inputs": yp["inputs"],
	"outputs": yp["outputs"],

	# t_CMakeLists.txt
	"project_name": yp["project_name"],
	"dependencies": yp["dependencies"],
}

with open(central_node, mode="w", encoding="utf-8") as results:
	results.write(central_node_template.render(context))
	print(f"... wrote {central_node}")

with open(CMakeLists, mode="w", encoding="utf-8") as results:
	results.write(CMakeLists_template.render(context))
	print(f"... wrote {CMakeLists}")

with open(package, mode="w", encoding="utf-8") as results:
	results.write(package_template.render(context))
	print(f"... wrote {package}")
