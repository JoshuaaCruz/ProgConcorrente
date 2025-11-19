from time import sleep
from random import randint
from threading import Thread, Lock, Condition

def produtor():
  global buffer
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    with lock:
      while len(buffer) == tam_buffer:
        print('>>> Buffer cheio. Produtor ira aguardar.')
        lugar_no_buffer.wait()    # aguarda que haja lugar no buffer
      buffer.append(item)
      print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))
      item_no_buffer.notify_all()

def consumidor():
  global buffer
  for i in range(10):
    with lock:
      while len(buffer) == 0:
        print('>>> Buffer vazio. Consumidor ira aguardar.')
        item_no_buffer.wait()   # aguarda que haja um item para consumir 
      item = buffer.pop(0)
      print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
      lugar_no_buffer.notify_all()
    sleep(randint(0,2))         # fica um tempo consumindo...

buffer = []
tam_buffer = 5
lock = Lock()
lugar_no_buffer = Condition(lock)
item_no_buffer = Condition(lock)


N = 70 #Parâmetro de qtd de Threads

produtores = []
consumidores = []
for i in range(N):
  produtores.append(Thread(target=produtor))
  consumidores.append(Thread(target=consumidor))

for i in range(N):
  produtores[i].start()
  consumidores[i].start()

for i in range(N):
  produtores[i].join()
  consumidores[i].join()
"""

prod1 = Thread(target=produtor)  
prod2 = Thread(target=produtor)

cons1 = Thread(target=consumidor)
cons2 = Thread(target=consumidor) 

prod1.start()
prod2.start()

cons1.start()
cons2.start()

prod1.join()
prod2.join()

cons1.join()
cons2.join() 
"""