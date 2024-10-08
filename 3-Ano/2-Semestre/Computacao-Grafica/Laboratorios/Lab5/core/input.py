"""Input management"""
import pygame
from OpenGL.GL import *

class Input(object):
    """Manages the users commands"""
    def __init__(self) -> None:
        """User terminated?"""
        self.quit = False
        # lists to store key states
        # down, up: discrete event; lasts for one iteration
        # pressed: continuous event, between down and up events
        self.key_down_list = []
        self.key_pressed_list = []
        self.key_up_list = []
    
    # functions to check key states
    def isKeyDown(self, keyCode):
        return keyCode in self.key_down_list
    def isKeyPressed(self, keyCode):
        return keyCode in self.key_pressed_list
    def isKeyUp(self, keyCode):
        return keyCode in self.key_up_list

    def update(self):
        """Manage user input events"""
        # Reset discrete key states
        self.key_down_list = []
        self.key_up_list = []
        # Iterate to detect changes since last check
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.quit = True
            # Check for key-down and key-up events;
            # get name of key from event and append to or remove from corresponding lists
            if event.type == pygame.KEYDOWN:
                key_name = pygame.key.name(event.key)
                self.key_down_list.append(key_name)
                self.key_pressed_list.append(key_name)
            if event.type == pygame.KEYUP:
                key_name = pygame.key.name(event.key)
                self.key_pressed_list.remove(key_name)
                self.key_up_list.append(key_name)
            
            # Movimento
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT :
                    glTranslatef(-1.0,0,0.0)
                if event.key == pygame.K_RIGHT :
                    glTranslatef(1.0,0,0.0)
                if event.key == pygame.K_UP :
                    glTranslatef(0.0,0,-1.0)
                if event.key == pygame.K_DOWN :
                    glTranslatef(0.0,0,1.0)
