class Card:

  def __init__(self, name, cost, text):
    self.name = name
    self.cost = cost
    self.text = text

  def setCost(self, cost):
    self.cost = cost

  def setText(self, text):
    self.text = text

class CreatureCard(Card):
  def __init__(self, name, cost, discard, text, dmg, hp, typeC, affinity):
    self.name = name
    self.cost = int(cost)
    self.discard = int(discard)
    self.text = text
    self.dmg = int(dmg)
    self.hp = int(hp)
    self.typeC = typeC
    self.affinity = affinity

  def outputCard(self):
    print(self.name)
    print("Creature -",self.typeC)
    print(self.cost, "-",self.affinity)
    print("DMG :",self.dmg,"|","HP :",self.hp)
    print(self.text)

'''
cardA = Card("Blue 2", 2,"Blue")
print(cardA.cost)
print(cardA.text)
cardA.setCost(1)
print(cardA.cost)
cardA.setText("Cheese")
print(cardA.text, '\n')
'''

cardB = CreatureCard("Zombie",1,2,"\"A mindless Zombie\"",2,1,"Undead","Night")
cardB.outputCard()
