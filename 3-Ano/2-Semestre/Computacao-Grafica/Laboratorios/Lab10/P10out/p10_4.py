import math

from core.base import Base
from core_ext.camera import Camera
from core_ext.mesh import Mesh
from core_ext.renderer import Renderer
from core_ext.scene import Scene
from core_ext.texture import Texture
from geometry.rectangle import RectangleGeometry
from geometry.sphere import SphereGeometry
from material.texture import TextureMaterial
from extras.axes import AxesHelper
from extras.grid import GridHelper
from extras.movement_rig import MovementRig
from geometry.tree import treeGeometry
from geometry.rock import rockGeometry
from core.obj_reader import my_obj_reader


class Example(Base):
    """
    Render a textured skysphere and a textured grass floor.
    Add camera movement: WASDRF(move), QE(turn), TG(look).
    """
    def initialize(self):
        print("Initializing program...")
        self.renderer = Renderer()
        self.scene = Scene()
        self.camera = Camera(aspect_ratio=800/600)
        self.rig = MovementRig()
        self.rig.add(self.camera)
        self.scene.add(self.rig)
        self.rig.set_position([0, 1, 4])

        axes = AxesHelper(axis_length=2)
        self.scene.add(axes)
        grid = GridHelper(
            size=20,
            grid_color=[1, 1, 1],
            center_color=[1, 1, 0]
        )
        grid.rotate_x(-math.pi / 2)
        self.scene.add(grid)

        sky_geometry = SphereGeometry(radius=50)
        sky_material = TextureMaterial(texture=Texture(file_name="images/sky.jpg"))
        sky = Mesh(sky_geometry, sky_material)
        self.scene.add(sky)
        grass_geometry = RectangleGeometry(width=100, height=100)
        grass_material = TextureMaterial(
            texture=Texture(file_name="images/sand.jpg"),
            property_dict={"repeatUV": [50, 50]}
        )
        grass = Mesh(grass_geometry, grass_material)
        grass.rotate_x(-math.pi/2)
        self.scene.add(grass)

        # Load the texture
        grid_texture_tree = Texture(file_name="images/palmtree.jpg")
        material_tree = TextureMaterial(texture=grid_texture_tree)

        # Read the OBJ file, now including UV coordinates
        obj_data_tree = my_obj_reader('core/test3.obj')  # Replace with the real path to your OBJ file
        # No need for a separate 'color_data' here since it's not used with texture material
        geometry_tree = treeGeometry(vertex_data=obj_data_tree['vertices'], color_data=[0, 0, 0], uv_data=obj_data_tree['uvs'])
        
        # Create the mesh with the sea geometry and texture material
        self.tree_mesh = Mesh(
            geometry=geometry_tree,
            material=material_tree
        )

        # Load the texture
        grid_texture_rock = Texture(file_name="images/rock.jpg")
        material_rock = TextureMaterial(texture=grid_texture_rock)

        # Read the OBJ file, now including UV coordinates
        obj_data_rock = my_obj_reader('core/rock.obj')  # Replace with the real path to your OBJ file
        # No need for a separate 'color_data' here since it's not used with texture material
        geometry_rock = rockGeometry(vertex_data=obj_data_rock['vertices'], color_data=[0, 0, 0], uv_data=obj_data_rock['uvs'])
        
        # Create the mesh with the sea geometry and texture material
        self.rock_mesh = Mesh(
            geometry=geometry_rock,
            material=material_rock
        )

        self.scene.add(self.tree_mesh)
        self.scene.add(self.rock_mesh)
        
    def update(self):
        self.rig.update(self.input, self.delta_time)
        self.renderer.render(self.scene, self.camera)

        # Define movement speed for the sea_mesh
        move_speed = 0.3

        # Move the sea_mesh based on keyboard input, using different keys to avoid conflict
        if self.input.is_key_down('i'):  # Move forward
            self.tree_mesh.translate(0, 0, -move_speed)
        if self.input.is_key_down('k'):  # Move backward
            self.tree_mesh.translate(0, 0, move_speed)
        if self.input.is_key_down('j'):  # Move left
            self.tree_mesh.translate(-move_speed, 0, 0)
        if self.input.is_key_down('l'):  # Move right
            self.tree_mesh.translate(move_speed, 0, 0)
        if self.input.is_key_down('u'):  # Move up
            self.tree_mesh.translate(0, move_speed, 0)
        if self.input.is_key_down('o'):  # Move down
            self.tree_mesh.translate(0, -move_speed, 0)


# Instantiate this class and run the program
Example(screen_size=[800, 600]).run()
