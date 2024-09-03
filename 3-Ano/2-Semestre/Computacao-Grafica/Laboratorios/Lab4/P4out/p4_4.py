"""Animation example"""
import OpenGL.GL as GL
from core.base import Base
from core.utils import Utils
from core.attribute import Attribute
from core.uniform import Uniform
import math, random

class Example(Base):
    """ Animate colored circle moving across screen """
    def initialize(self):
        print("Initializing program...")
        # Initialize program #
        vs_code = """
            in vec3 position;
            in vec3 color;
            out vec3 vertexColor;
            uniform vec3 translation;
            void main()
            {
                vec3 pos = position + translation;
                gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
                vertexColor = color;
            }
        """
        fs_code = """
            in vec3 vertexColor;
            out vec4 fragColor;
            void main()
            {
                fragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0);
            }
        """
        self.program_ref = Utils.initialize_program(vs_code, fs_code)
        # Render settings #
        GL.glClearColor(0.0, 0.0, 0.0, 1.0)
        # Set up vertex array object #
        vao_ref = GL.glGenVertexArrays(1)
        GL.glBindVertexArray(vao_ref)
        # Set up vertex attribute (for a circle) and color #
        num_vertices = 32
        position_data = [[0.0, 0.0, 0.0]]  # Center of the circle
        color_data = [[1.0, 0.7, 0.5]]  # Color for the center
        for i in range(num_vertices + 1):
            angle = 2 * math.pi * i / num_vertices
            x = math.cos(angle) * 0.2
            y = math.sin(angle) * 0.2
            position_data.append([x, y, 0.0])
            # Generate color for each vertex
            color_data.append([0.5, math.cos(angle), 0.5])
        self.vertex_count = len(position_data)
        position_attribute = Attribute('vec3', position_data)
        position_attribute.associate_variable(self.program_ref, 'position')
        color_attribute = Attribute('vec3', color_data)
        color_attribute.associate_variable(self.program_ref, 'color')
        # Set up uniforms #
        self.translation = Uniform('vec3', [0.0, 0.0, 0.0])
        self.translation.locate_variable(self.program_ref, 'translation')

    def update(self):
        self.translation.data[0] = 0.75 * math.cos(random.randint(1, 10))
        self.translation.data[1] = 0.75 * math.sin(random.randint(1, 10))
        
        GL.glClear(GL.GL_COLOR_BUFFER_BIT)
        GL.glUseProgram(self.program_ref)
        self.translation.upload_data()
        GL.glDrawArrays(GL.GL_TRIANGLE_FAN, 0, self.vertex_count)
        self.clock.tick(5)
# Instantiate this class and run the program
Example().run()
