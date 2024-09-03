import pygame

class Input(object):

	def __init__(self):
	
		# has the user quit the application?
		self.quit = False

	def update(self):
		# iterate over all user input events (such as keyboard or
		# mouse)that occurred since the last time events were checked
		for event in pygame.event.get():
		# quit event occurs by clicking button to close window
			if event.type == pygame.QUIT:
				self.quit = True
			#########	
			#	P3	#
			#########
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_r or event.key == pygame.K_g or event.key == pygame.K_b:
					print(pygame.key.name(event.key))
					