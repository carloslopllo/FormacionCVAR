from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
	return LaunchDescription([
		Node(
			package='cpp_pubsub',
			executable='data',
			name='remapping_1'
		),
		Node(
			package='cpp_pubsub',
			executable='data',
			name='remapping_2',
			remappings=[
				('/data1', '/data2'),
			]
		)
	])
