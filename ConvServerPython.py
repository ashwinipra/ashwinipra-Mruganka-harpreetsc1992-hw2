import socket
import sys

## Function to process requests
def process(conn):
    # read userInput from client
    conn.send("Welcome, you are connected to g-oz server.\n")
    userInput = conn.recv(BUFFER_SIZE)
    if not userInput:
        print "Error reading message"
        sys.exit(1)
        
    print ("Received message: ", userInput)
    reply = func(userInput)

def func(userInput):
	mysplit = userInput.split(" ")#split the input string
	try:						#checking for numerals
		mysplit[2]=float(mysplit[2])#the numeral value
		if mysplit[0]== "g" and mysplit[1] == "oz":#if input is g oz number
			convAns = mysplit[2]*0.035274
		elif mysplit[0]== "oz" and mysplit[1] == "g":#if input is oz g number
			convAns=mysplit[2]/0.035274
		else:
			conn.send("Error! Invalid Input!\n")
		convAns=str(convAns)#convert to string
		convAns=convAns+"\n"
		conn.send(convAns)	#send the converted answer to the client
		conn.close()
		return convAns
	except ValueError:			#if not a numeral
		print "No Number Entered, Closing this Connection"
		conn.send("Enter a number")
		conn.close()
		return null
	


### Main code run when program is started
BUFFER_SIZE = 1024
interface = ""

# if input arguments are wrong, print out usage
if len(sys.argv) != 2:
	print >> sys.stderr, "usage: python {0} portnum\n".format(sys.argv[0])
    	sys.exit(1)

portnum = int(sys.argv[1])

# create socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((interface, portnum))
s.listen(5)

while True:
    # accept connection and print out info of client
    	conn, addr = s.accept()
    	print 'Accepted connection from client', addr
    	process(conn)
s.close()
