from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
	return LaunchDescription ([
		Node (
			package='central_node_pkg',
			executable='central_node',
			name='central_node'
		),

		Node (
			package='pub_node_pkg',
			executable='pub_node',
			name='data1'
		),

		Node (
			package='pub_node_pkg',
			executable='pub_node',
			name='data2',
			remappings=[
				('/data1', '/data2'),
			]
		),
	])
