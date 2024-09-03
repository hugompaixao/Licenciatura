"""Example of billboarding"""

from core.base import Base
from core.matrix import Matrix
from core_ext.mesh import Mesh
from core_ext.camera import Camera
from core_ext.renderer import Renderer
from core_ext.scene import Scene
from core_ext.texture import Texture
from geometry.box import BoxGeometry
from geometry.rectangle import RectangleGeometry
from extras.movement_rig import MovementRig
from extras.text_texture import TextTexture
from material.texture import TextureMaterial
import math

class Example(Base):
    """
    Demonstrate the use of look_at in billboarding
    keys: ADRF
    """
    def initialize(self):
        """Defining example"""
        print("Initializing program...")
        self.renderer = Renderer()
        self.scene = Scene()
        self.camera = Camera(aspect_ratio=800/600)
        self.rig = MovementRig()
        self.rig.add(self.camera)
        self.rig.set_position([0, 1, 5])
        self.scene.add(self.rig)

        # Create label (billboard)
        label_texture = TextTexture(text=" This is a Crate. ",
                                    system_font_name="Arial Bold",
                                    font_size=40, font_color=[0, 0, 200],
                                    image_width=256, image_height=128,
                                    align_horizontal=0.5, align_vertical=0.5,
                                    image_border_width=4,
                                    image_border_color=[255, 0, 0])
        label_material = TextureMaterial(label_texture)
        label_geometry = RectangleGeometry(width=1, height=0.5)
        self.label = Mesh(label_geometry, label_material)
        #self.scene.add(self.label)

        # Create crate
        crate_geometry = BoxGeometry()
        crate_texture = Texture("images/crate.jpg")
        crate_material = TextureMaterial(label_texture)
        self.crate = Mesh(crate_geometry, crate_material)
        self.crate.set_position([2, 1, 0])  # Set initial position
        self.scene.add(self.crate)

        # Define variables for jump animation
        self.jump_height = 2.0  # Maximum height of jump
        self.jump_duration = 2.0  # Duration of jump animation
        self.jump_timer = 0.0

    def update(self):
        self.rig.update(self.input, self.delta_time)

        # Update jump animation for both objects
        self.jump_timer += self.delta_time
        if self.jump_timer >= self.jump_duration:
            self.jump_timer = 0.0  # Reset timer after jump completes
        
        # Calculate y position based on jump animation
        jump_progress = min(self.jump_timer / self.jump_duration, 1.0)
        jump_height = math.sin(jump_progress * math.pi) * self.jump_height

        # Update crate position
        crate_position = [0, 1 + jump_height, 0]
        self.crate.set_position(crate_position)

        # Update label position below crate with an offset
        label_offset = 0.75  # Adjust this value as needed
        label_position = [2, 1 - 0.5 - label_offset + jump_height, 0]
        #self.label.set_position(label_position)

        self.renderer.render(self.scene, self.camera)


# Instantiate this class and run the program
Example(screen_size=[800, 600]).run()