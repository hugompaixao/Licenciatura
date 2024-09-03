"""Textures examples"""
import math
from core.base import Base
from core_ext.camera import Camera
from core_ext.mesh import Mesh
from core_ext.renderer import Renderer
from core_ext.scene import Scene
from core_ext.texture import Texture
from extras.movement_rig import MovementRig
from geometry.tree import treeGeometry
from material.texture import TextureMaterial
from extras.axes import AxesHelper
from extras.grid import GridHelper
from core.obj_reader import my_obj_reader  # Ensure this is the updated version that returns UVs


class Example(Base):
    def initialize(self):
        print("Initializing program...")
        self.renderer = Renderer()
        self.scene = Scene()
        self.camera = Camera(aspect_ratio=800/600)
        self.rig = MovementRig()
        self.rig.add(self.camera)
        self.rig.set_position([0.5, 1, 5])
        self.scene.add(self.rig)
        axes = AxesHelper(axis_length=2)
        self.scene.add(axes)
        grid = GridHelper(
            size=20,
            grid_color=[1, 1, 1],
            center_color=[1, 1, 0]
        )
        grid.rotate_x(-math.pi / 2)
        self.scene.add(grid)

        # Load the texture
        grid_texture = Texture(file_name="images/palmtree.jpg")
        material = TextureMaterial(texture=grid_texture)

        # Read the OBJ file, now including UV coordinates
        obj_data = my_obj_reader('core/test.obj')  # Replace with the real path to your OBJ file
        # No need for a separate 'color_data' here since it's not used with texture material
        geometry = treeGeometry(vertex_data=obj_data['vertices'], color_data=[0, 0, 0], uv_data=obj_data['uvs'])
        
        # Create the mesh with the sea geometry and texture material
        self.tree_mesh = Mesh(
            geometry=geometry,
            material=material
        )
        self.scene.add(self.tree_mesh)

    def update(self):
        self.rig.update(self.input, self.delta_time)
        self.renderer.render(self.scene, self.camera)


# Instantiate this class and run the program
Example(screen_size=[800, 600]).run()
