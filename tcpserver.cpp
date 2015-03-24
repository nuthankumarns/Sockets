#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <sstream>
#include <vector>

/*char insertToDatabase(char *params, int size)
{
std::cout << params[8] << std::endl;
  return 0;


}*/

  int main()
  {

    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.


    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
  /* Change me */
    char const *server = "localhost";
    char const *user = "root";
    char const *password = "v3h1c13";
    char const *database = "vts"; 


    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
    // is created in c++, it will be given a block of memory. This memory is not nessesary
    // empty. Therefor we use the memset function to make sure all fields are NULL.
    memset(&host_info, 0, sizeof host_info);

    std::cout << "Setting up the structs..."  << std::endl;

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
    host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

    // Now fill up the linked list of host_info structs with google's address information.
    status = getaddrinfo(NULL, "5556", &host_info, &host_info_list);
    // getaddrinfo returns 0 on succes, or some other value when an error occured.
    // (translated into human readable text by the gai_gai_strerror function).
    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;


    std::cout << "Creating a socket..."  << std::endl;
    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
      host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;

    std::cout << "Binding socket..."  << std::endl;
    // we use to make the setsockopt() function to make sure the port is not in use
    // by a previous execution of our code. (see man page for more information)
    int yes = 1;
    status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "bind error" << std::endl ;

    std::cout << "Listen()ing for connections..."  << std::endl;
    status =  listen(socketfd, 5);
    if (status == -1)  std::cout << "listen error" << std::endl ;


    int new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_sd == -1)
    {
      std::cout << "listen error" << std::endl ;
    }
    else
    {
      std::cout << "Connection accepted. Using new socketfd : "  <<  new_sd << std::endl;
    }


    std::cout << "Waiting to recieve data..."  << std::endl;
    ssize_t bytes_recieved;
    char incomming_data_buffer[1000];
    bytes_recieved = recv(new_sd, incomming_data_buffer,1000, 0);
    // If no data arrives, the program will just wait here until some data arrives.
    if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
    if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
    std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
    incomming_data_buffer[bytes_recieved] = '\0';


    // char buffer[] = incomming_data_buffer;
    char* s;
    s = strtok (incomming_data_buffer,",");
    int step=0;
//const int size=30;
    char* params[30];

    while (s != NULL)
    {
     printf ("%s\n",s);
     params[step]=s;
     step++;
     s = strtok (NULL, ",");
   }



   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }

   /* send SQL query */
  std::cout << params[1]  << std::endl;
//char *last=params[10];
  std::ostringstream sql;

  sql << "INSERT INTO `vts`.`device_data` (`DeviceDataId`, `IntegratorId`, `ClientId`, `SerialNumber`, `DriverCode`, `UnitTamperStatus`,"
   <<"`Latitude`, `Longitude`, `DateTime`, `GPSStatus`, `GSMSignalStrength`, `Speed`, `Heading`, `FuelLevelVoltage`,"
   <<"`BatteryLevelVoltage`, `EngineStatus`, `IO-1-Status`, `IO-2-Status`, `IO-3-Status`, `IO-4-Status`, `IO-5-Status`, `IO-6-Status`, `IO-7-Status`, `IO-8-Status`, "
   <<"`FirmwareVersion`, `StringId`, `RebootStatus`, `Separator`, `CheckSum`) VALUES (NULL, '"<<params[1]<<"', '"<<params[2]<<"', '"<<params[3]<<"', '"<<params[4]<<"', '"<<params[5]<<"', "
   <<"'"<<params[6]<<"', '"<<params[7]<<"', '"<<params[8]<<"', '"<<params[9]<<"', '"<<params[10]<<"', '"<<params[11]<<"', '"<<params[12]<<"', '"<<params[13]<<"', '"<<params[14]<<"', '"<<params[15]<<"'," 
   <<"'"<<params[16]<<"', '"<<params[17]<<"', '"<<params[18]<<"', '"<<params[19]<<"', '"<<params[20]<<"', '"<<params[21]<<"', '"<<params[22]<<"'," 
   <<" '"<<params[23]<<"', '"<<params[24]<<"', '"<<params[25]<<"', '"<<params[26]<<"', '"<<params[27]<<"', '"<< params[28] <<"')";
if (mysql_query(conn, sql.str().c_str())) {
  fprintf(stderr, "%s\n", mysql_error(conn));
  exit(0);
}else{
  printf("Inserted a  record\n");
}

res = mysql_use_result(conn);
// fprintf(stderr, "%s\n", res);
   /* output table name */
  // printf("MySQL Tables in mysql database:\n");
//   while ((row = mysql_fetch_row(res)) != NULL)
 //     printf("%s \n", row[0]);

   /* close connection */
mysql_free_result(res);
mysql_close(conn);

 //std::cout << "Length:"<< s <<std::endl;
   // std::cout << "Length:"<< (sizeof(s)) <<std::endl;

   // std::cout << params << std::endl;
std::cout << "Conn to db" << std::endl ;
   // insertToDatabase(params, size);
//std::cout << db  << std::endl;
std::cout << "send()ing back a message..."  << std::endl;
char msg[] = "thank you.";
int len;
ssize_t bytes_sent;
len = strlen(msg);
bytes_sent = send(new_sd, msg, len, 0);

std::cout << "Stopping server..." << std::endl;
freeaddrinfo(host_info_list);
close(new_sd);
close(socketfd);

return 0 ;


}





