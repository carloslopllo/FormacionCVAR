import os
import sys
import yaml
from jinja2 import Environment, FileSystemLoader

# sys.argv[1] = /home/vboxuser/ros2_ws/manifest/central_node_pkg/manifest.yaml
# sys.argv[2] = /home/vboxuser/ros2_ws/templates/central_node_pkg/

if len(sys.argv) != 3:
	print("Usage:", sys.argv[0], "/ros2_ws/manifest/central_node_pkg/manifest.yaml", "/ros2_ws/templates/central_node_pkg/")
	sys.exit(1)

with open(sys.argv[1], "r") as f:
	try:
		yp = yaml.safe_load(f)
	except yaml.YAMLError as e:
		raise ValueError(f"Error while parsing YAML file: {e}")

default_type = "REQUIRED"

for section in ("buildtools", "dependencies", "testing_CMakeLists"):
	if section in yp:
		for item in yp[section]:
			item.setdefault("type", default_type)

context = {
	# package
	"project_name": yp["project_name"],
	"project_version": yp["project_version"],
	"project_description": yp["project_description"],
	"maintainer_email": yp["maintainer_email"],
	"maintainer": yp["maintainer"],
	"license": yp["license"],

	# dependencies
	"buildtools": yp["buildtools"],
	"dependencies": yp["dependencies"],
	"testing_CMakeLists": yp["testing_CMakeLists"],
	"testing_package": yp["testing_package"],

	# class config
	"class_name": yp["class_name"],
	"includes": yp["includes"],
	"inputs": yp["inputs"],
	"outputs": yp["outputs"],
}

for path, _, files in os.walk(sys.argv[2]):
	for file in files:
		path_file = os.path.join(path, file)
		environment = Environment(loader=FileSystemLoader(path))

		path_file_template = environment.get_template(file)
		new_path_file = path_file.replace("templates", "src")
		new_path_file = new_path_file.replace(".jinja2", "")

		try:
			open(new_path_file, mode="w", encoding="utf-8")
		except IOError:
			os.makedirs(os.path.dirname(new_path_file))
		finally:
			with open(new_path_file, mode="w", encoding="utf-8") as results:
				results.write(path_file_template.render(context))
				print(f"... wrote {new_path_file}")
