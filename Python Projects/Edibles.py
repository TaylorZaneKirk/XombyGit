edibles = ["ham", "spam", "eggs","nuts"]
for food in edibles:
    if food == "spam":
        #so disgusted with spam, I can't eat anything else
        print("No more spam please!")
        break
    print("Great, delicious " + food)

#loop else, only executed if loop not broken
else: 
    print("I am so glad: No spam!")

print("Finally, I finished stuffing myself")

