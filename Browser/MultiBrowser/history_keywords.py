import sqlite3
import os
#Get History Keywords typed in some navigators
LOCAL = os.getenv("LOCALAPPDATA")
TEMP = os.getenv("TEMP")
Browsers = {"Chrome":LOCAL+"\\Google\\Chrome\\User Data\\Default",
               "Brave":LOCAL+"\\BraveSoftware\\Brave-Browser\\User Data\\Default"}


def getHistory(Path):

    if os.path.isfile(Path+"\\History"):
        return Path+"\\History"
    return False
for browser,path in Browsers.items():
    if getHistory(path)==False:
        continue
    pathn = TEMP+"\\History"+nav
    with open(pathn,'wb') as f:
        with open(getHistory(path),'rb') as l:
            f.write(l.read())
    path=pathn
    db =sqlite3.connect(path) 
    cur = db.cursor()
    try:
        z = cur.execute("SELECT * FROM keyword_search_terms")
    except sqlite3.OperationalError:
        continue
    result = z.fetchall()
    for x in result:
        print("="*50)

        print("Browser:"+browser)
        print("ID:"+str(x[1]))
        print("Keyword:"+x[2])
    cur.close()
    db.close()
    os.remove(path)
    