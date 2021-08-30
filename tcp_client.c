#include<sys/types.h>        
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netinet/ip.h> /* superset of previous */
#include<strings.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>

void error(char *msg)
{
  
      perror(msg);
      exit(1);
}


int main(int argc,char *argv[])
{
      int sockfd;
      int connectfd;


      struct sockaddr_in serv_addr;


      int port_no;
      
       bzero((char*) &serv_addr,sizeof(serv_addr)); 

      char buf[1024];
      int ret;

       if(argc < 2)
       {
	       printf("kindly provide the port number");
	       
       }

       port_no = atoi(argv[1]);

       serv_addr.sin_family = AF_INET;
       serv_addr.sin_port = htons(port_no);
       serv_addr.sin_addr.s_addr = INADDR_ANY;
       

       
       sockfd = socket(AF_INET,SOCK_STREAM,0);

       if(sockfd < 0)
       {
             perror("Error in creating socket");
             exit(1);
       }



       connectfd = connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));

       if(connectfd == 0)
       {
	       printf("connection successful\n");
       }
       else
       {
	       printf("connection unsuccessful\n");
       }

       char readbuf[1024];
       char writebuf[1024];

       

       ret=fork();

 if(ret ==  0)
       {
       while(1)
       {
       bzero(buf,1024);
       read(sockfd,&buf,sizeof(buf));
       printf("Msg from server %s\n",buf);
       }
       }

       else if(ret > 0)
       {
        while(1)
        {
        int buf_count=0;	       
       bzero(buf,1024);
       printf("Msg to server\n");
       while((buf[buf_count++] = getchar()) != '\n');
       write(sockfd,&buf,sizeof(buf));
        }
       }

       else
               printf("Failed to create child ");

       close(sockfd);
      

       exit(0);

}
        
 
