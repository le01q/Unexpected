import sqlite3
import os
import datetime
LOCAL = os.getenv("LOCALAPPDATA")
TEMP = os.getenv("TEMP")
Browsers = {"Chrome":LOCAL+"\\Google\\Chrome\\User Data\\Default",
               "Brave":LOCAL+"\\BraveSoftware\\Brave-Browser\\User Data\\Default"}

def date_from_webkit(webkit_timestamp): #Convert Chrome format time to human time 
    epoch_start = datetime.datetime(1601,1,1)
    delta = datetime.timedelta(microseconds=int(webkit_timestamp))
    return epoch_start + delta
def format_datetime(dt, template='{0.day:02d}/{0.month:02d}/{0.year:4d} {0.hour:2d}:{0.minute:2d}'):
    return template.format(dt)
def getHistory(Path):

    if os.path.isfile(Path+"\\History"):
        return Path+"\\History"
    return False
for nav,path in Browsers.items(): #Iterate Browsers path
    if getHistory(path)==False:
        continue
    pathn = TEMP+"\\History"+nav #Create a temp file 
    with open(pathn,'wb') as f: #Copy file into the temp file to bypass any database block
        with open(getHistory(path),'rb') as l:
            f.write(l.read())
    path=pathn
    db =sqlite3.connect(path)
    cur = db.cursor()
    try:
        z = cur.execute("SELECT * FROM urls") #Select urls 
    except sqlite3.OperationalError:
        os.remove(path) #Remove the file if dont exists history
        continue
        
    result = z.fetchall()
    for x in result:
        title = x[2] #The title of website
        url = x[1] #The url
        
        last_timed=date_from_webkit(x[5]) # The last time that visited the site 
        last_timer=format_datetime(last_timed) #Solve the bug that happend if year is <=1900
        views=x[3] #The views of site 
        print(50*"=") #Simple decorator
        print("Browser:"+nav)
        print("Title:"+title)
        print("URL:"+url)
        print("Last time seen:"+last_timer)
        print("Views:"+str(views))
    cur.close()
    db.close()
    #Important close the cursor and database 
    os.remove(path)
    #Delete the temp file
    