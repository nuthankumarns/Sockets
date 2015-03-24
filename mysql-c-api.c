/* 
See url for more info:
http://www.cyberciti.biz/tips/linux-unix-connect-mysql-c-api-program.html

*/
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(void) {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
  /* Change me */
   char *server = "localhost";
   char *user = "root";
   char *password = "v3h1c13";
   char *database = "vts";
   
   conn = mysql_init(NULL);
   
   /* Connect to database */
   if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(0);
   }

   /* send SQL query */

char *sql="INSERT INTO `vts`.`device_data` (`DeviceDataId`, `IntegratorId`, `ClientId`, `SerialNumber`, `DriverCode`, `UnitTamperStatus`, `Latitude`, `Longitude`, `DateTime`, `GPSStatus`, `GSMSignalStrength`, `Speed`, `Heading`, `FuelLevelVoltage`, `BatteryLevelVoltage`, `EngineStatus`, `IO-1-Status`, `IO-2-Status`, `IO-3-Status`, `IO-4-Status`, `IO-5-Status`, `IO-6-Status`, `IO-7-Status`, `IO-8-Status`, `FirmwareVersion`, `StringId`, `RebootStatus`, `Separator`, `CheckSum`) VALUES (NULL, 'ABCDE', 'ABCDE', 'A0002', '0', '0', '1302.82181', '07733.93711', '010315171307', '00', '00', '0.764', '230', '0.0123', '0.04', '0.04', '0', '0', '0', '0', '0', '0', '0', '0', 'V1.0', 'L0000', '0', '*', '6D')";
   if (mysql_query(conn, sql)) {
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
  
  return 0;
}
