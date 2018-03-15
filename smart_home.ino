
#include <Ethernet.h>
#include <SPI.h>

int lamp1 = 4;
int lamp2 = 5;


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE3};
byte ip[] = {192,168,2,20};
byte gateway[] = {192,168,2,1};
byte subnet[] = {255,255,255,0};

EthernetServer server(80);
String readString;

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  
  pinMode(lamp1,OUTPUT);
  pinMode(lamp2,OUTPUT);
  
  Ethernet.begin(mac,ip,gateway,subnet);
  Serial.print("Server Connected.");
  Serial.println(Ethernet.localIP());
}

void loop()
{

  //Create a Client Connection
  EthernetClient client = server.available();
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (readString.length() < 100)
          {
            readString+=c;  //readString = readString + c
          }
          
        if (c=='\n')
        {
          Serial.println(readString);
          
          client.println("HTTP/1.1 200 OK");    //Send new page
          client.println("Content-Type:text/html");
          client.println();
          
          client.println("<html>");
          client.println("<head>");
          client.println("<meta charset='utf8'>");
          client.println("<style>body{margin:60px 0px; text-align:center} a{text-decoration:none;width:75px;height:50px;border-color:black;border-top:2px solid;border-bottom:2px solid;border-right:2px solid;border-left:2px solid;border-radius:10px 10px 10px;padding:8px;text-align:center;} a:hover{color:green;}</style>");
          
          client.println("<title>Rozito.ir</title>");
          client.println("</head>");
          
          client.println("<body>");
          client.println("<H1>لینوکس برای زندگی</H1>");
          client.println("<hr />");
          client.println("<br />");
          
          client.println("<a href=\"/?button1on\"\">روشن کردن</a>");
          client.println("<a href=\"/?button1off\"\">خاموش کردن</a>");
          
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          
          client.println("<a href=\"/?button2on\"\">روشن کردن</a>");
          client.println("<a href=\"/?button2off\"\">خاموش کردن</a>");
          
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          
          client.println("<h4>Programmer : SSShojaei</h4>");
          client.println("<br />");
          client.println("</body>");
          client.println("</html>");
          
          delay(1);
          client.stop();
          
          //--------------------------------------
          if (readString.indexOf("?button1on")>0)
          {
            digitalWrite(lamp1,LOW);
          }
          
          if (readString.indexOf("?button1off")>0)
          {
            digitalWrite(lamp1,HIGH);
          }
          //--------------------------------------
          
          //--------------------------------------
          if (readString.indexOf("?button2on")>0)
          {
            digitalWrite(lamp2,LOW);
          }
          
          if (readString.indexOf("?button2off")>0)
          {
            digitalWrite(lamp2,HIGH);
          }
          //--------------------------------------
          
          readString = "";
          
        }
      }
    }
  }
}
