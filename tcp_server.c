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
      int bindfd;
      int listenfd;
      int acceptfd;
      


      struct sockaddr_in serv_addr;

      struct sockaddr_in client_addr;

      int port_no;
      int client_len;
      int no_of_backlog=5;
      
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


       bindfd = bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));

       if(bindfd < 0)
       {
	       perror("failed to bind");
	       exit(2);
       }
       else
       {
	       printf("server is running at port_number %d\n",port_no);
       }


       listenfd = listen(sockfd , no_of_backlog);

       if(listenfd)
       {
	       printf("fail to listen\n");
       }
       else
       {
	       printf("success to listen\n");
       }

       client_len = sizeof(client_addr);
       acceptfd = accept(sockfd,(struct sockaddr *)&client_addr,&client_len);

       if(acceptfd < 0)
       {
	       printf("accept system call fail");
	       exit(1);
       }
       else
       {
	       printf("accept system call pass %d\n",acceptfd);
       }

       bzero(buf,1024);

       ret = read(acceptfd,buf,sizeof(buf));

       if(ret < 0)
       {
	       perror("Data not received\n");
       }
       else
       {
	       printf("The data from client %s\n",buf);
       }

       char ack[1024] = "bingo,we got msg";

       ret=write(acceptfd,ack,sizeof(buf));

       if(ret < 0)
       {
	       perror("ack failed\n");
       }
       else
       {
	       printf("ack successfull\n");
       }

       close(sockfd);
       close(acceptfd);

       exit(0);

}
        
 
