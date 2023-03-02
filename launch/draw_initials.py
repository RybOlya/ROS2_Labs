from launch import LaunchDescription
from launch_ros.actions import Node
from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch.substitutions import FindExecutable
def generate_launch_description():
    ld = LaunchDescription(
        [
            Node(
                package="turtlesim",
                executable="turtlesim_node",
                name="turtlesim",
            ),
            Node(
                package='ros2_labs',
                executable='initials',
                name='initials'
        )
        ]
    )
    ld.add_action(
        ExecuteProcess(
            cmd=[
                [
                    FindExecutable(name="ros2"),
                    " service call ",
                    "/spawn ",
                    "turtlesim/srv/Spawn ",
                    "\"{x: 2.0, y: 6.0, theta: 1.57, name: 'turtle2'}\"",
                ]
            ],
            shell=True,
        )
    )
    return ld
