/*
 * bedrockProxy.c
 * (C) 2019, all rights reserved,
 *
 * This file is part of Vortex Desktop.
 *
 */

/*
 * DESCRIPTION:
 * Setup a tunnel to expose minecraft servers to LAN in Minecraft
 * Windows 10 Bedrock Version.
 *
 * usage: bedrockProxy.exe [DestIPv4Addr] [DestPort]
 */
// Default filter udp.DstPort == 19132

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "windivert.h"

#define ntohs(x)            WinDivertHelperNtohs(x)
#define ntohl(x)            WinDivertHelperNtohl(x)

#define htons(x)            WinDivertHelperHtons(x)
#define htonl(x)            WinDivertHelperHtonl(x)

#define MAXBUF              WINDIVERT_MTU_MAX
#define INET6_ADDRSTRLEN    45

/*
 * Helper function to convert String to UINT
 */
unsigned int convert(char *st) {
  char *x;
  for (x = st ; *x ; x++) {
    if (!isdigit(*x))
      return 0L;
  }
  return (strtoul(st, 0L, 10));
}

/*
 * Greeting texts and author information.
 */
void showGreetingTexts(){
  printf("--------------\n");
  printf("Eyy Welcome to Minecraft Bedrock Server Exposer! Here we expose your external servers to LAN tab of Minecraft :D ");
  printf("Current Version:%s\n", "1.0.0");
  printf("Author: Agent_Orange#9852 (Discord)\n");
  printf("This Module Is OpenSourced, Link- https://github.com/hari01584/libWin10MinecraftTunnel\n");
  printf("--------------\n\n\n");
}

/*
 * Entry.
 */
int __cdecl main(int argc, char **argv)
{
    HANDLE handle, console;
    UINT i;
    INT16 priority = 0;
    unsigned char packet[MAXBUF];
    UINT packet_len;
    WINDIVERT_ADDRESS addr;
    PWINDIVERT_IPHDR ip_header;
    PWINDIVERT_UDPHDR udp_header;
    UINT32 src_addr[4], dst_addr[4];
    UINT32 targetAddr;
    UINT16 targetPort;
    UINT64 hash;
    char src_str[INET6_ADDRSTRLEN+1], dst_str[INET6_ADDRSTRLEN+1];
    const char *err_str;
    LARGE_INTEGER base, freq;
    double time_passed;

    // Check arguments.
    switch (argc)
    {
        case 2:
            break;
        case 3:
            priority = (INT16)atoi(argv[2]);
            break;
        default:
            fprintf(stderr, "usage: %s [DestIPv4Addr] [DestPort]\n",
                argv[0]);
            fprintf(stderr, "examples:\n");
            fprintf(stderr, "\t%s \"149.56.206.101\" 19132\n", argv[0]);
            exit(EXIT_FAILURE);
    }

    // Get console for pretty colors.
  //  console = GetStdHandle(STD_OUTPUT_HANDLE);
    showGreetingTexts();

    // Sanitize args
    if(!WinDivertHelperParseIPv4Address(argv[1], &targetAddr)){
      fprintf(stderr, "error: bad target address(%d) - %s", GetLastError(), argv[1]);
      return -1;
    }
    if((targetPort = convert(argv[2])) == 0L){
      fprintf(stderr, "error: bad target port(%s)", argv[2]);
      return -1;
    }
    // Divert traffic matching the filter:
   char filter[80];
   sprintf(filter, "udp.DstPort == 19132 or udp.DstPort == %s", argv[2]);
   handle = WinDivertOpen(filter, WINDIVERT_LAYER_NETWORK, priority,
        WINDIVERT_FLAG_FRAGMENTS);
    if (handle == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_INVALID_PARAMETER &&
            !WinDivertHelperCompileFilter(filter, WINDIVERT_LAYER_NETWORK,
                NULL, 0, &err_str, NULL))
        {
            fprintf(stderr, "error: invalid filter \"%s\"\n", err_str);
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "error: failed to open the WinDivert device (%d)\n",
            GetLastError());
        exit(EXIT_FAILURE);
    }

    // Max-out the packet queue:
    if (!WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_LENGTH,
            WINDIVERT_PARAM_QUEUE_LENGTH_MAX))
    {
        fprintf(stderr, "error: failed to set packet queue length (%d)\n",
            GetLastError());
        exit(EXIT_FAILURE);
    }
    if (!WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_TIME,
            WINDIVERT_PARAM_QUEUE_TIME_MAX))
    {
        fprintf(stderr, "error: failed to set packet queue time (%d)\n",
            GetLastError());
        exit(EXIT_FAILURE);
    }
    if (!WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_SIZE,
            WINDIVERT_PARAM_QUEUE_SIZE_MAX))
    {
        fprintf(stderr, "error: failed to set packet queue size (%d)\n",
            GetLastError());
        exit(EXIT_FAILURE);
    }

    // Set up timing:
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&base);

    printf("Starting tool! Go to LAN tab of minecraft bedrock to see your server!!");
    // Main loop:
    while (TRUE)
    {
        // Read a matching packet.
        if (!WinDivertRecv(handle, packet, sizeof(packet), &packet_len, &addr))
        {
            fprintf(stderr, "warning: failed to read packet (%d)\n",
                GetLastError());
            continue;
        }

        // Print info about the matching packet.
        WinDivertHelperParsePacket(packet, packet_len, &ip_header, NULL,
            NULL, NULL, NULL, NULL, &udp_header, NULL,
            NULL, NULL, NULL);
        if (ip_header == NULL)
        {
            fprintf(stderr, "warning: junk packet\n");
        }

        // Dump packet info:
        // putchar('\n');
        // SetConsoleTextAttribute(console, FOREGROUND_RED);
        // time_passed = (double)(addr.Timestamp - base.QuadPart) /
        //     (double)freq.QuadPart;
        // hash = WinDivertHelperHashPacket(packet, packet_len, 0);
        // printf("Packet [Timestamp=%.8g, Direction=%s IfIdx=%u SubIfIdx=%u "
        //     "Loopback=%u Hash=0x%.16llX]\n",
        //     time_passed, (addr.Outbound?  "outbound": "inbound"),
        //     addr.Network.IfIdx, addr.Network.SubIfIdx, addr.Loopback, hash);
        if (ip_header != NULL && udp_header != NULL)
        {
            //WinDivertHelperParseIPv4Address("149.56.206.101", &target);
            //ip_header->DstAddr = htonl(target);

            UINT32 srcAddr = ntohl(ip_header->SrcAddr);
            UINT32 dstAddr = ntohl(ip_header->DstAddr);
            WinDivertHelperFormatIPv4Address(srcAddr,
                src_str, sizeof(src_str));
            WinDivertHelperFormatIPv4Address(dstAddr,
                dst_str, sizeof(dst_str));

            // SetConsoleTextAttribute(console,
            //     FOREGROUND_GREEN | FOREGROUND_RED);
            // printf("IPv4 [Version=%u HdrLength=%u TOS=%u Length=%u Id=0x%.4X "
            //     "Reserved=%u DF=%u MF=%u FragOff=%u TTL=%u Protocol=%u "
            //     "Checksum=0x%.4X SrcAddr=%s DstAddr=%s]\n",
            //     ip_header->Version, ip_header->HdrLength,
            //     ntohs(ip_header->TOS), ntohs(ip_header->Length),
            //     ntohs(ip_header->Id), WINDIVERT_IPHDR_GET_RESERVED(ip_header),
            //     WINDIVERT_IPHDR_GET_DF(ip_header),
            //     WINDIVERT_IPHDR_GET_MF(ip_header),
            //     ntohs(WINDIVERT_IPHDR_GET_FRAGOFF(ip_header)), ip_header->TTL,
            //     ip_header->Protocol, ntohs(ip_header->Checksum), src_str,
            //     dst_str);


            UINT16 srcPort = ntohs(udp_header->SrcPort);
            UINT16 dstPort = ntohs(udp_header->DstPort);
            // printf("UDP [SrcPort=%u DstPort=%u Length=%u "
            //     "Checksum=0x%.4X]\n",
            //     srcPort, dstPort,
            //     ntohs(udp_header->Length), ntohs(udp_header->Checksum));

            if(dstAddr == targetAddr && dstPort == targetPort){
              //SetConsoleTextAttribute(console, FOREGROUND_GREEN);
              printf("Successfully Connected!\n");
              break;
            }
            if(dstPort == 19132){
              ip_header->DstAddr = htonl(targetAddr);
              udp_header->DstPort = htons(targetPort);
            }
        }

        WinDivertHelperCalcChecksums(packet, packet_len, &addr, 0);
        if (!WinDivertSend(handle, packet, packet_len, NULL, &addr))
        {
            fprintf(stderr, "warning: failed to reinject packet (%d)\n",
                GetLastError());
        }
    }
}
