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
from geometry.leaf import leafGeometry
from geometry.stone import stoneGeometry
from geometry.sea import seaGeometry
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

        # Tree 
        # Load the texture
        grid_texture_tree = Texture(file_name="images/palmtree.jpg")
        material_tree = TextureMaterial(texture=grid_texture_tree)

        # Read the OBJ file, now including UV coordinates
        obj_data_tree = my_obj_reader('core/tree.obj')  # Replace with the real path to your OBJ file
        # No need for a separate 'color_data' here since it's not used with texture material
        geometry_tree = treeGeometry(vertex_data=obj_data_tree['vertices'], color_data=[0, 0, 0], uv_data=obj_data_tree['uvs'])
        
        # Create the mesh with the sea geometry and texture material
        self.tree_mesh = Mesh(
            geometry=geometry_tree,
            material=material_tree
        )

        self.scene.add(self.tree_mesh)
        
        # Leafs
        # Load the texture
        grid_texture_leaf = Texture(file_name="images/grass.jpg")
        material_leaf = TextureMaterial(texture=grid_texture_leaf)

        # Read the OBJ file, now including UV coordinates
        obj_data_leaf = my_obj_reader('core/leafs.obj')  # Replace with the real path to your OBJ file
        # No need for a separate 'color_data' here since it's not used with texture material
        geometry_leaf = leafGeometry(vertex_data=obj_data_leaf['vertices'], color_data=[0, 0, 0], uv_data=obj_data_leaf['uvs'])
        
        # Create the mesh with the sea geometry and texture material
        self.leaf_mesh = Mesh(
            geometry=geometry_leaf,
            material=material_leaf
        )

        self.scene.add(self.leaf_mesh)

        # Stone
        # Load the texture
        grid_texture_stone = Texture(file_name="images/rock.jpg")
        material_stone = TextureMaterial(texture=grid_texture_stone)

        # Read the OBJ file, now including UV coordinates
        obj_data_stone = my_obj_reader('core/stone.obj')  # Replace with the real path to your OBJ file
        # No need for a separate 'color_data' here since it's not used with texture material
        geometry_stone = stoneGeometry(vertex_data=obj_data_stone['vertices'], color_data=[0, 0, 0], uv_data=obj_data_stone['uvs'])
        
        # Create the mesh with the sea geometry and texture material
        self.stone_mesh = Mesh(
            geometry=geometry_stone,
            material=material_stone
        )

        self.scene.add(self.stone_mesh)

        # Sea
        # Load the texture
        grid_texture_sea = Texture(file_name="images/sky.jpg")
        material_sea = TextureMaterial(texture=grid_texture_sea)

        # Read the OBJ file, now including UV coordinates
        obj_data_sea = my_obj_reader('core/sea.obj')  # Replace with the real path to your OBJ file
        # No need for a separate 'color_data' here since it's not used with texture material
        geometry_sea = seaGeometry(vertex_data=obj_data_sea['vertices'], color_data=[0, 0, 0], uv_data=obj_data_sea['uvs'])
        
        # Create the mesh with the sea geometry and texture material
        self.sea_mesh = Mesh(
            geometry=geometry_sea,
            material=material_sea
        )

        self.scene.add(self.sea_mesh)
        
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
