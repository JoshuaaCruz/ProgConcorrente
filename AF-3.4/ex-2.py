from time import sleep
from random import randint
from threading import Thread, Semaphore

def produtor():
  global buffer
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    # verifica se há lugar no buffer

    sem_prod.acquire()

    buffer.append(item)
    print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))

    sem_cons.release()

def consumidor():
  global buffer
  for i in range(10):
    # aguarda que haja um item para consumir 
    
    sem_cons.acquire()
    item = buffer.pop(0)
    print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
    sleep(randint(0,2))         # fica um tempo consumindo...
    sem_prod.release()

buffer = []
tam_buffer = 46984
# cria semáforos
sem_prod = Semaphore(tam_buffer)
sem_cons = Semaphore(0)

prod = Thread(target=produtor) 
cons = Thread(target=consumidor) 
prod.start()
cons.start()
prod.join()
cons.join() 