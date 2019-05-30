 #include <ESP8266WiFi.h>

const char* ssid = "ELETRICA";
const char* password = "123456789";

int ledPin = D2; // GPIO2
int ledPin2 = D3; // GPIO2
int ledPin3 = D4;
int ledPin4 = D5;
int ledPin5 = D6;


WiFiServer server(80);

void setup() {
pinMode(LED_BUILTIN, OUTPUT); // BLINK LED
Serial.begin(115200);
delay(10);

pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, LOW);

pinMode(ledPin2, OUTPUT);
digitalWrite(ledPin2, LOW);

pinMode(ledPin3, OUTPUT);
digitalWrite(ledPin3, LOW);

pinMode(ledPin4, OUTPUT);
digitalWrite(ledPin4, LOW);

pinMode(ledPin5, OUTPUT);
digitalWrite(ledPin5, LOW);


// Connect to WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
server.begin();
Serial.println("Server started");

// Print the IP address
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");

}

void loop() {
// Check if a client has connected
WiFiClient client = server.available();
if (!client) {
return;
}

// Wait until the client sends some data
Serial.println("new client");
while (!client.available()) {
delay(1);
}

// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

// Match the request

int value = LOW;
int value2 = LOW;
int value3 = LOW;
int value4 = LOW;
int value5 = LOW;


bool logged = false;

if (request.indexOf("/LED=ON") != -1) {
digitalWrite(ledPin, LOW);
digitalWrite(LED_BUILTIN, LOW); 
value = HIGH;
logged = true;
}
if (request.indexOf("/LED=OFF") != -1) {
digitalWrite(LED_BUILTIN, HIGH); //EXAMPLE LED
digitalWrite(ledPin, HIGH);
value = LOW;
logged = true;
}

if (request.indexOf("/LED2=ON") != -1) {
digitalWrite(ledPin2, LOW);
value2 = LOW;
logged = true;
}
if (request.indexOf("/LED2=OFF") != -1) {
digitalWrite(ledPin2, HIGH);
value2 = HIGH;
logged = true;
}

if (request.indexOf("/LED3=ON") != -1) {
digitalWrite(ledPin3, LOW);
value3 = LOW;
logged = true;
}
if (request.indexOf("/LED3=OFF") != -1) {
digitalWrite(ledPin3, HIGH);
value3 = HIGH;
logged = true;
}

if (request.indexOf("/LED4=ON") != -1) {
digitalWrite(ledPin4, LOW);
value4 = LOW;
logged = true;
}
if (request.indexOf("/LED4=OFF") != -1) {
digitalWrite(ledPin4, HIGH);
value4 = HIGH;
logged = true;
}
if (request.indexOf("/LED5=ON") != -1) {
digitalWrite(ledPin5, HIGH);
value5 = HIGH;
logged = true;
delay(200);
digitalWrite(ledPin5, LOW);
value5 = LOW;
}




// Set ledPin according to the request
//digitalWrite(ledPin, value);

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");

client.println("<!DOCTYPE html>");
client.println("<html lang=\"pt-br\">");

client.println("<head>");
  client.println("<meta charset=\"utf-8\">");
  client.println("<title>Automated Ruler</title>");
  client.println("<link rel=\"stylesheet\" type=\"text/css\" href=\"_css/\"/>");
  client.println("<link rel=\"stylesheet\" type=\"text/css\" href=\"_css/\"/>");
client.println("</head>");
client.println("<script language=\"javascript\" src=\"_javascript/funcoes.js\"></script>");

client.println("<style type=\"text/css\" media=\"screen\">");
client.println("body {");
  client.println("background-color: #dddddd;");   //*pode ser usado em hexadecimal> background-color: #a1d3ef */
  client.println("color :rgba(0,0,0,1);"); //*o ultimo é a transparencia desejada de 0.0 a 1.0*/ 
  client.println("font-family: Arial, sans-serif;");
client.println("}");
client.println("header#cabecalho{");
  client.println("border-bottom: 2px #606060 solid;");
  client.println("height: 80px;");
client.println("}");
client.println("header#cabecalho h1{");
  client.println("font-family: Arial, sans-serif;");
  client.println("font-size: 40pt;");
  client.println("color: #606060;");
  client.println("text-shadow: 1px 1px 1px rgba(0,0,0,.6);");
  client.println("padding: 0px;");
  client.println("margin-bottom: 0px;");
client.println("}");
client.println("header#cabecalho h2{");
  client.println("font-family: Arial, sans-serif;");
  client.println("color: #888888;");
  client.println("font-size: 20pt;");
  client.println("padding: 0px;");
  client.println("margin-top: 0px;");
client.println("}");
client.println("div#interface {");
  client.println("background-color: #ffffff;");
  client.println("margin-top: -25px;");
  client.println("margin-right: auto;");
  client.println("margin-left: auto;");
  client.println("margin-bottom: 0px;");
  client.println("box-shadow: 0px 0px 10px rgba(0,0,0,.5);");
  client.println("padding: 10px 10px 10px 10px;");
  client.println("width: 900px;");
  //* o menu esta em posição absoluta entao ele fica fora dessa div */
client.println("}");
client.println("div.col-md-6 a.btn-on{");
  client.println("background-color: rgb(147,219,112);");
  client.println("font-size: 56px;");
  client.println("color: white;");
  client.println("box-shadow: 0px 0px 10px rgba(0,0,0,.5);");
  client.println("padding-top: 15px;");
  client.println("padding-bottom: 15px;");
  client.println("text-decoration: none;");
client.println("}");

client.println("div.col-md-6 a.btn-off{");
  client.println("background-color: rgb(200,0,90);");
  client.println("font-size: 56px;");
  client.println("color: white;");
  client.println("box-shadow: 0px 0px 10px rgba(0,0,0,.5);");
  client.println("margin-left: 5px;");
  client.println("padding-top: 15px;");
  client.println("padding-bottom: 15px;");
  client.println("text-decoration: none;");
client.println("}");
client.println("div.col-md-6 a:hover{");
  client.println("text-decoration: underline;");
client.println("}");
client.println("section#corpo{");
  client.println("display: block;"); //* divide em blocos o site e Float indica o lado que vai ser dividido*/
  client.println("width: 578px;");
  client.println("float: left;");
  client.println("border-right: 2px solid #606060;");
  client.println("padding-right: 15px;");
client.println("}");
client.println("article#noticia-principal h2{");
  client.println("font-size: 14pt;");
  client.println("color: #606060;");
  client.println("background-color: #dddddd;");
  client.println("padding: 5px 0px 5px 10px;");
  client.println("margin: 10px 0px 10px 0px;");
client.println("}");
client.println("header#cabecalho-artigo h1{");
  client.println("font-family: Arial, sans-serif;");
  client.println("font-size: 28pt;");
  client.println("color: #606060;");
  client.println("margin: 0px;");
client.println("}");
client.println("header#cabecalho-artigo h2{");
  client.println("font-size: 17pt;");
  client.println("color: #cecece;");
  client.println("background-color: #ffffff;");
  client.println("margin: 0px;");
client.println("}");
client.println("header#cabecalho-artigo h3{");
  client.println("font-size: 14px;");
  client.println("color: #606060;");
client.println("}");
client.println("header#cabecalho-artigo h3.direita{");
  client.println("text-align: right;");
client.println("}");
client.println("aside#lateral{");
  client.println("display: block;");
  client.println("width: 280px;");
  client.println("float: right;");
  client.println("background-color: #dddddd;");
  client.println("padding: 10px;");
  client.println("margin-top: 10px;");
  client.println("box-shadow: 2px 2px 2px rgba(0,0,0,.5);");
client.println("}");
client.println("aside#lateral h1{");
  client.println("font-family: Arial, sans-serif;");
  client.println("font-size: 27pt;");
  client.println("color: #606060;");
  client.println("margin-top: 0px;");
  client.println("margin-bottom: -5px;");

client.println("}");
client.println("aside#lateral h2{");
  client.println("font-size: 16pt;");
  client.println("background-color: #606060;");
  client.println("color: #ffffff;");
  client.println("padding: 5px;");
client.println("}");
client.println("aside#lateral h3{");
  client.println("font-family: Arial, sans-serif;");
  client.println("font-size: 15pt;");
  client.println("color: #606060;");
  client.println("margin-top: 0px;");
client.println("}");
client.println("footer#rodape{");
  client.println("clear: both;"); //* quebra a divisão acima de SECTION E ASIDE*/
  client.println("text-align: center;");
  client.println("text-decoration: none;");
  client.println("border-top: 2px #606060 solid;");
  client.println("padding: 10px;");
client.println("}");
client.println(".btn-enter{");
client.println("font-size: 20pt;");
client.println("color: #ffffff;");
client.println("height: 40px;");
client.println("width: 140pt;");
client.println("background-color: rgb(0,150,230);");
client.println("box-shadow: 0px 0px 10px rgba(0,0,0,.5);");
client.println("margin-left: 10pt;");
client.println("}");
client.println("</style>");

client.println("<script type=\"text/javascript\">");
client.println("function Login() {");
client.println("var done=0;");
client.println("var usuario = document.getElementById('USERNAME').value;");
client.println("var senha= document.getElementById('PASSWORD').value;");
client.println("console.log(usuario);");
client.println(" console.log(senha);");
client.println(" if (usuario==\"admin\" && senha==\"eletrica\") {");
client.println("done=1;");
client.println("document.getElementById( 'login' ).style.display = 'none';");
client.println("document.getElementById( 'corpo' ).style.display = '';");
client.println("document.getElementById( 'lateral' ).style.display = '';");
client.println("}");
  client.println("if (done==0) { alert(\"Dados incorretos, tente novamente\"); }");
client.println("}");
client.println("</script>");

client.println("<body>");
client.println("<div id=\"interface\">");
  
  client.println("<header id=\"cabecalho\">");
    client.println("<hgroup>");
    
    client.println("<h1>Automated Ruler Control</h1>");
    client.println("</hgroup>");
  client.println("</header>");

if (logged == false){
client.println("<section id=\"login\">");
client.println("<br>");
  client.println("<H1>USERNAME: <input type=\"text\" id=\"USERNAME\" style=\"font-size: 20pt; height: 40px; width: 200pt;\"></H1>");
  client.println("<br>");
  client.println("<H1>PASSWORD: <input type=\"password\" id=\"PASSWORD\" style=\"font-size: 20pt; height: 40px; width: 200pt;\"></H1>");
  client.println("<br>");
  client.println("<button onclick=\"Login()\" class=\"btn-enter\">ENTER</button></section>");
  client.println("<br>");
client.println("</section>");
client.println("<section id=\"corpo\" style=\"display: none;\">"); //<!--dividir em sessao, pode usar SECTION, ASSIDE E FOOTER, para dividir o site-->
}
else
{
client.println("<section id=\"corpo\">"); //<!--dividir em sessao, pode usar SECTION, ASSIDE E FOOTER, para dividir o site-->
}
client.println("<article id=\"noticia-principal\">");
client.println("<header id=\"cabecalho-artigo\">");
client.println("<hgroup>  <!--agrupa-->");
client.println("<h3>Tecnologia > Automação Domótica</h3>");
client.println("<h1>Controle Residencial AB.Software</h1>");
//client.println("<h2>por AB.SOFTWARES</h2>");
//client.println("<h3 class=\"direita\">Atualizado em 2018</h3>");
client.println("</hgroup>");
client.println("</header>");
client.println("<h2>Selecione Ligar ou Desligar para a tomada desejada.</h2>");

client.println("<h1>");
client.println("<div class='col-md-6'>");
client.println("<div class='alert alert-info text-center' role='alert'>TOMADA 1</div>");
client.println("<br>");
//client.println("<br>");
client.println("<a class='btn-on' href=\"/LED=ON\"> &nbsp;&nbsp;&nbsp;Ligar&nbsp;&nbsp;&nbsp; </a>");
client.println("<a class='btn-off' href=\"/LED=OFF\"> &nbsp;&nbsp;&nbsp;Desligar&nbsp;&nbsp;&nbsp; </a>");
client.println("</div>");
client.println("<br>");
client.println("<br>");
client.println("<br>");

client.println("<div class='col-md-6'>");
client.println("<div class='alert alert-info text-center' role='alert'>TOMADA 2</div>");
client.println("<br>");
//client.println("<br>");
client.println("<a class='btn-on' href=\"/LED2=ON\"> &nbsp;&nbsp;&nbsp;Ligar&nbsp;&nbsp;&nbsp; </a>");
client.println("<a class='btn-off' href=\"/LED2=OFF\"> &nbsp;&nbsp;&nbsp;Desligar&nbsp;&nbsp;&nbsp; </a>");
client.println("</div>");
client.println("<br>");
client.println("<br>");
client.println("<br>");

client.println("<div class='col-md-6'>");
client.println("<div class='alert alert-info text-center' role='alert'>TOMADA 3</div>");
client.println("<br>");
//client.println("<br>");
client.println("<a class='btn-on' href=\"/LED3=ON\"> &nbsp;&nbsp;&nbsp;Ligar&nbsp;&nbsp;&nbsp; </a>");
client.println("<a class='btn-off' href=\"/LED3=OFF\"> &nbsp;&nbsp;&nbsp;Desligar&nbsp;&nbsp;&nbsp; </a>");
client.println("</div>");
client.println("<br>");
client.println("<br>");
client.println("<br>");

client.println("<div class='col-md-6'>");
client.println("<div class='alert alert-info text-center' role='alert'>TOMADA 4</div>");
client.println("<br>");
//client.println("<br>");
client.println("<a class='btn-on' href=\"/LED4=ON\"> &nbsp;&nbsp;&nbsp;Ligar&nbsp;&nbsp;&nbsp; </a>");
client.println("<a class='btn-off' href=\"/LED4=OFF\"> &nbsp;&nbsp;&nbsp;Desligar&nbsp;&nbsp;&nbsp; </a>");
client.println("</div>");
client.println("<br>");
client.println("<br>");
client.println("</h1>");

client.println("</article>");
client.println("</section>");
if (logged == false){
client.println("<aside id=\"lateral\" style=\"display: none;\">");
}
else
{
client.println("<aside id=\"lateral\">");
}

client.println("<h1>Instruções</h1>");
client.println("<h2>1 - Tomadas</h2>");
client.println("<h3><p>As tomadas estão identificadas aos seus respectivos números no protótipo.<br>");


client.println("<br>O botão abaixo realiza a abertura e fechamento do portão.</p></h3>");
  
client.println("<br>");
client.println("<br>");

client.println("<div class='col-md-6'>");
client.println("<div class='alert alert-info text-center' role='alert'><strong>ABRIR/FECHAR PORTAO</strong></div>");
client.println("<br>");
client.println("<br>");

client.println("&nbsp;&nbsp;&nbsp;&nbsp;<a class='btn-on' href=\"/LED5=ON\"> &nbsp;&nbsp;&nbsp;Pulso&nbsp;&nbsp;&nbsp; </a>");
client.println("</div>");
client.println("<br>");
client.println("<br>");

  
client.println("</aside>");
client.println("<footer id=\"rodape\">");
client.println("<h4>Copyright &copy; 2018 - by AB.Software");
client.println("<br>");
client.println("<a href=\"http://www.Facebook.com\" target=\"_blank\">Facebook</a> |&nbsp;<a href=\"http://www.twitter.com\" target=\"_blank\">Twitter</a></h4>");
client.println("</footer>");
client.println("</div>");
client.println("</body>");
client.println("</html>");


delay(1);
Serial.println("Client disonnected");
Serial.println("");

}
