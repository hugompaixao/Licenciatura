"""An example of a basic scene: spinning cube"""

from core.base import Base
from core_ext.camera import Camera
from core_ext.mesh import Mesh
from core_ext.renderer import Renderer
from core_ext.scene import Scene
from geometry.ellipsoid import EllipsoidGeometry
from material.surface import SurfaceMaterial
from material.point import PointMaterial


class Example(Base):
    """ Render a basic scene that consists of a spinning cube """
    def initialize(self):
        self.rotation_x = 0.04514
        self.rotation_y = 0.02337
        self.rotation_z = 0.01337
        print("Initializing program...")
        self.renderer = Renderer()
        self.scene = Scene()
        self.camera = Camera(aspect_ratio=800/600)
        self.camera.set_position([0, 0, 4])
        geometry = EllipsoidGeometry()
        # material = PointMaterial(property_dict={"baseColor": [1, 1, 0], "pointSize": 5})
        material = SurfaceMaterial(property_dict={"useVertexColors": True})
        # material = SurfaceMaterial(
        #     property_dict= {
        #         "useVertexColors": True,
        #         "wireframe": True,
        #         "lineWidth": 8
        #     }
        # )
        self.mesh = Mesh(geometry, material)
        self.scene.add(self.mesh)

    def update(self):
        if self.input.is_key_pressed('r'):
            self.rotation_x = 0.04514
            self.rotation_y = 0.02337
            self.rotation_z = 0.01337
        if self.input.is_key_pressed('s'):
            if self.rotation_x <= 0:
                self.rotation_x = 0
            else: 
                self.rotation_x -= 0.001 
            if self.rotation_y <= 0:
                self.rotation_y = 0
            else:
                self.rotation_y -= 0.001 
            if self.rotation_z <= 0:
                self.rotation_z = 0  
            else:  
                self.rotation_z -= 0.001
        if self.input.is_key_pressed('f'):
            self.rotation_x += 0.005 
            self.rotation_y += 0.002
            self.rotation_z += 0.001
        if self.input.is_key_pressed('x'):
            self.rotation_x = 0.03 
            self.rotation_y = 0 
            self.rotation_z = 0
        if self.input.is_key_pressed('y'):
            self.rotation_x = 0 
            self.rotation_y = 0.03
            self.rotation_z = 0
        if self.input.is_key_pressed('z'):
            self.rotation_x = 0 
            self.rotation_y = 0
            self.rotation_z = 0.03
        self.mesh.rotate_y(self.rotation_x)
        self.mesh.rotate_x(self.rotation_y)
        self.mesh.rotate_z(self.rotation_z)
        self.renderer.render(self.scene, self.camera)


# Instantiate this class and run the program
Example(screen_size=[800, 600]).run()
