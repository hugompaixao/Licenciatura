import sys

from core.base import Base
from core_ext.camera import Camera
from core_ext.mesh import Mesh
from core_ext.renderer import Renderer
from core_ext.scene import Scene
from core_ext.texture import Texture
from geometry.rectangle import RectangleGeometry
from material.material import Material

class Example(Base):
    """
    Combine rippling effect and distortion over time by using a RGB noise texture with pseudo-random 
    uv-coordinates and adding a sine-based displacement to the V component of the UV coordinates in 
    the fragment shader.
    """
    def initialize(self):
        print("Initializing program...")
        print()
        print("Note: the fragment shader now applies both the rippling effect and the distortion based on the RGB noise texture to the texture")
        self.renderer = Renderer()
        self.scene = Scene()
        self.camera = Camera(aspect_ratio=800/600)
        self.camera.set_position([0, 0, 1.5])
        vertex_shader_code = """
            uniform mat4 projectionMatrix;
            uniform mat4 viewMatrix;
            uniform mat4 modelMatrix;
            in vec3 vertexPosition;
            in vec2 vertexUV;
            out vec2 UV;
            
            void main()
            {
                gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
                UV = vertexUV;
            }
        """
        fragment_shader_code = """
            uniform sampler2D rgbNoise;
            uniform sampler2D texture;
            in vec2 UV;
            uniform float time;
            out vec4 fragColor;
            
            void main()
            {
                vec2 uvShift = UV + vec2(-0.033, 0.07) * time;
                vec4 noiseValues = texture2D(rgbNoise, uvShift);
                vec2 uvNoise = UV + 0.01 * noiseValues.rg;
                vec2 shiftUV = uvNoise + vec2(0, 0.2 * sin(6.0 * uvNoise.x + time));
                fragColor = texture2D(texture, shiftUV);
            }
        """
        rgb_noise_texture = Texture("images/rgb-noise.jpg")
        grid_texture = Texture("images/crate.jpg")
        self.combined_material = Material(vertex_shader_code, fragment_shader_code)
        self.combined_material.add_uniform("sampler2D", "rgbNoise", [rgb_noise_texture.texture_ref, 1])
        self.combined_material.add_uniform("sampler2D", "texture", [grid_texture.texture_ref, 2])
        self.combined_material.add_uniform("float", "time", 0.0)
        self.combined_material.locate_uniforms()

        geometry = RectangleGeometry(2, 1)
        self.mesh = Mesh(geometry, self.combined_material)
        self.scene.add(self.mesh)

    def update(self):
        self.combined_material.uniform_dict["time"].data += self.delta_time
        self.renderer.render(self.scene, self.camera)

# Instantiate this class and run the program
Example(screen_size=[800, 600]).run()
