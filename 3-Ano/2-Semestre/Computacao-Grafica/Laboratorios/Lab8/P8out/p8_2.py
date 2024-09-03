import numpy as np
from core.base import Base
from core_ext.camera import Camera
from core_ext.mesh import Mesh
from core_ext.renderer import Renderer
from core_ext.scene import Scene
from geometry.geometry import Geometry
from material.point import PointMaterial
from material.line import LineMaterial

class Example(Base):
    def initialize(self):
        print("Initializing program...")
        self.renderer = Renderer()
        self.scene = Scene()
        self.camera = Camera(aspect_ratio=800/600)
        self.camera.set_position([0, 0, 5])
        self.time = 0
        self.vs_code = """
        uniform mat4 projectionMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 modelMatrix;
        in vec3 vertexPosition;
        void main()
        {
            gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
        }
        """
        self.fs_code = """
        uniform vec3 baseColor;
        out vec4 fragColor;
        void main()
        {
            fragColor = vec4(baseColor, 1.0);
        }
        """
        self.point_material = PointMaterial(self.vs_code, self.fs_code, {"baseColor": [1, 1, 1], "pointSize": 10})
        self.line_material = LineMaterial(self.vs_code, self.fs_code, {"baseColor": [1, 0, 0], "lineWidth": 2})
        # Create initial mesh
        self.create_mesh(0)

    def create_mesh(self, phase_shift):
        # Create new geometry for the sine wave with the given phase shift
        geometry = Geometry()
        x_values = np.linspace(-3.2, 3.2, 30)
        y_values = np.sin(x_values + phase_shift)
        position_data = [[x, y, 0] for x, y in zip(x_values, y_values)]
        geometry.add_attribute("vec3", "vertexPosition", position_data)
        geometry.count_vertices()
        # Create new meshes
        new_point_mesh = Mesh(geometry, self.point_material)
        new_line_mesh = Mesh(geometry, self.line_material)
        # Replace the old meshes with the new ones
        if hasattr(self, 'point_mesh'):
            self.scene.remove(self.point_mesh)
            self.scene.remove(self.line_mesh)
        self.point_mesh = new_point_mesh
        self.line_mesh = new_line_mesh
        self.scene.add(self.point_mesh)
        self.scene.add(self.line_mesh)

    def update(self):
        self.time += self.delta_time
        phase_shift = self.time 
        self.create_mesh(phase_shift)  # Recreate the mesh with the new phase shift
        self.renderer.render(self.scene, self.camera)

# Instantiate this class and run the program
Example(screen_size=[800, 600]).run()