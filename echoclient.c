#include <sys/types.h> /* socket() を使うために必要*/
#include <sys/socket.h> /* 同上*/
#include <netinet/in.h> /* INET ドメインのソケットを使うために必要*/
#include <netdb.h>/* gethostbyname()を使うために必要*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define PORT 10120

int main(int argc,char **argv){
	int sock;
	struct sockaddr_in host;
	struct hostent *hp;
	int rbuf_len,sbuf_len;
	char rbuf[1024],sbuf[1024];
	/*echoclint exp030 の２つ分なので　argc != 2　*/
	if (argc != 2) {
		fprintf(stderr,"Usage: %s hostname message\n",argv[0]);
		exit(1);
	}/*ソケットの生成*/
	if ( ( sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) ) < 0) {
		perror("socket");
		exit(1);
	}
	}/* host(ソケットの接続先)の情報設定*/
	bzero(&host,sizeof(host));
	host.sin_family=AF_INET;
	host.sin_port=htons(PORT);
	if ( ( hp = gethostbyname(argv[1]) ) == NULL ) {
		fprintf(stderr,"unknown host %s\n",argv[1]);
		exit(1);
	}
	bcopy(hp->h_addr,&host.sin_addr,hp->h_length);/*パケットの送信*/
	
	/* connect() でhost と接続する*/
	if( connect(sock, (struct sockaddr_in *)&addr, sizeof(addr)) < 0 )
        {
			perror( server );
			close( s );
			return( -1 );
	    }
	/* パケットの受信と表示*/
	while(1){
	// 受け入れるパケットの送信元を指定(0.0.0.0 で任意のアドレスからのパケットを受信)
		bzero(&sender,sizeof(sender));
		sender_len = sizeof(sender);
		if((len = recvfrom(sock, buf, sizeof(buf), 0,
			(struct sockaddr*)&sender, &sender_len)) < 0){
			perror("recvfrom");
			exit(1);
		}
		inet_ntop(AF_INET, &sender.sin_addr, senderstr, sizeof(senderstr));
		write(1, buf, len);
		printf(" from [%s:%d]\n", senderstr, sender.sin_port);
	}
}
