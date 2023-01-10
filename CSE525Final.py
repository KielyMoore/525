from operator import attrgetter
import cv2

samples = 20

def preview():
    
    vid = cv2.VideoCapture(0) # create video capture object

    #camera set up
    while(True):
          
        # Capture the video frame
        _, frame = vid.read()
        frame = cv2.flip(frame, 0)
        frame = cv2.flip(frame, 1)
        height = frame.shape[0]
        width = frame.shape[1]
        
        # Draw text
        cv2.putText(frame, "Press Q", (5,20), cv2.FONT_HERSHEY_DUPLEX, 0.5, (0,255,0), 1, cv2.LINE_AA)
        cv2.putText(frame, "Submit", (5,35), cv2.FONT_HERSHEY_DUPLEX, 0.5, (0,255,0), 1, cv2.LINE_AA)  
        
        # Draw guide lines
        start = int((width - height) / 2)
        end = width - start
        for i in [0,1,2,3]:
            cv2.line(frame, (start, int(i * height / 3)), (end, int(i * height / 3)), (255,0,0), 1)
            cv2.line(frame, (int(start + i *((end - start) / 3)), 0), (int(start + i *((end - start) / 3)), height), (0,0,255), 1)
        
        cv2.imshow('frame', frame)
         
        # Wait for q to be pressesd
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    #remove preview window
    cv2.destroyAllWindows()

    # Take pictures of each of the board spaces
    for i in range(samples):
        
        _, samp = vid.read()
        samp = cv2.flip(samp, 0)
        samp = cv2.flip(samp, 1)
        height = samp.shape[0]
        width = samp.shape[1]
        start = int((width - height) / 2)
        end = width - start

        #crop image
        samp = samp[:, start:end]
        height = samp.shape[0] # get new height
        width = samp.shape[1] # and new width

        #turn down the contrast to make qr codes more readable
        adjusted = cv2.convertScaleAbs(samp, alpha=0.85, beta=1)
            
        #convert image to gray scale
        gray = cv2.cvtColor(adjusted, cv2.COLOR_BGR2GRAY)

        #turn image into binary black and white
        (thresh, baw) = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

        # subdivide image into tile pieces
        for y in range(3):
            start_y = int(y * height/3)
            end_y = int((y+1) * height/3)
            for x in range(3):
                start_x = int(x * width/3)
                end_x = int((x+1) * width/3)
                code = baw[start_y:end_y, start_x:end_x]
                
                # save images to seperate folders based on position
                cv2.imwrite(f'folder{x}{y}/img{i}.jpeg',code)
    
    # release the camera object
    vid.release()
  
# returns the initial state of the board    
def readBoard():

    board =[['0','0','0'],['0','0','0'],['0','0','0']]
    detector = cv2.QRCodeDetector()
    
    # Read the images
    for y in range(3):
        for x in range (3):
            flag = True
            for i in range(samples):
                img = cv2.imread(f'/home/group3/folder{x}{y}/img{i}.jpeg');
                data, _, _ = detector.detectAndDecode(img);
                if data is not None and data != "":
                    board[y][x] = data[0:1]
                    flag = False
                    break
            if flag:
                board[y][x] = "-"

    # Display the board to user
    print("\nDisplaying Board")
    for i in board:
        for j in i:
            print(j, end=" ")
        print()
    
    return board
  
  
def hLookUp(val):
    if val == '1': return 0,0
    elif val == '2': return 0,1
    elif val == '3': return 0,2
    elif val == '4': return 1,0
    elif val == '5': return 1,1
    elif val == '6': return 1,2
    elif val == '7': return 2,0
    elif val == '8': return 2,1
    elif val == '-': return 2,2
    else: return -1,-1


class State:
    def __init__(self, depth, parent):
        self.depth = depth
        self.parent = parent
        self.board = []
        self.fscore = 0
        
    def setBoard(self, board):
        for y in board:
            temp = []
            for x in y:
                temp.append(x)
            self.board.append(temp)
        return self;
            
    def find(self, val):
        for i in range(len(self.board)):
            for j in range(len(self.board)):
                if self.board[i][j] == val:
                    return i,j
    
    def setFscore(self):
        hscore = 0
        for x in range(len(self.board)):
            for y in range(len(self.board)):
                hx,hy = hLookUp(self.board[x][y])
                hscore += abs(x-hx) + abs(y-hy)
        self.fscore = hscore + self.depth
        return self
        

def createChild(state, x1, y1, x2, y2):
    newState = State(state.depth+1, state)
    newState.setBoard(state.board)
    newState.board[x1][y1] = newState.board[x2][y2]
    newState.board[x2][y2] = '-'
    newState.setFscore()
    return newState

def main():
    goal = [['1','2','3'], ['4','5','6'], ['7','8','-']]

    solution = []
        
    openStates = []
    closedBoards = []

    #get inital state from camera
    while True:
        preview()
        initBoard = readBoard()
        count = 0
        for i in initBoard:
            for j in i:
                if j == "-":
                    count += 1
        if count != 1:
            print("Board did not read properly")
            print("Try again")
        else:
            break
   
    
    # Create initial State and add to open states
    initState = State(0,0).setBoard(initBoard).setFscore()
    openStates.append(initState)

    #Begin A* 
    searching = True
    while searching:
        
        #Select Next State
        openStates.sort(key=attrgetter("fscore"))
        current = openStates.pop(0)
        closedBoards.append(current.board)
        
        #Solution Found
        if current.board == goal:
            searching = False
            
            #generate solve instructions
            while (current.parent != 0):
                y1,x1 = current.find('-')
                y2,x2 = current.parent.find('-')
                direction = "start"
                if(x2>x1):
                    direction="right"
                elif(x2<x1):
                    direction="left"
                elif(y2<y1):
                    direction="up"
                elif(y2>y1):
                    direction="down"
                solution.insert(0, f'Move: {current.parent.board[y1][x1]} {direction}')
                current = current.parent
        
        #Generate Child States
        else:
            x,y = current.find("-")
            if x+1 <= 2:
                child = createChild(current, x, y, x+1, y)
                if child.board not in closedBoards:
                    openStates.append(child)
            
            if y+1 <= 2:
                child = createChild(current, x, y, x, y+1)
                if child.board not in closedBoards:
                    openStates.append(child)
            
            if x-1 >= 0:
                child = createChild(current, x, y, x-1, y)
                if child.board not in closedBoards:
                    openStates.append(child)
            
            if y-1 >= 0:
                child = createChild(current, x, y, x, y-1)
                if child.board not in closedBoards:
                    openStates.append(child)
    
    #Print instructions to user 
    count = 1
    print("Instruction for solving puzzle: ")
    for item in solution:
        print(str(count)+". "+str(item))
        count += 1;
        pass


if __name__ == "__main__":
    main()
    pass
