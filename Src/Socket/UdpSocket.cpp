/*
 * This file is part of the rFactor-Nesim.
 *
 * Martin Galpin (m@66laps.com).
 *
 * Copyright(c) 2011 66laps Limited.
 *
 * This file may be licensed under the terms of of the
 * GNU General Public License Version 3 (the ``GPL'').
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the GPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the GPL along with this
 * program. If not, go to http://www.gnu.org/licenses/gpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include "UdpSocket.hpp"

#include <stdio.h>

UdpSocket::UdpSocket(const char* host, int port) 
    : mHost(host), mPort(port)
{
}

UdpSocket::~UdpSocket(void)
{
}

void UdpSocket::Open(void)
{
    if(WSAStartup(MAKEWORD(2, 0), &mWinsockData) != 0)
        fprintf(stderr, "WSAStartup() failed");   

    if ((mSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        perror("socket() failed");   

    memset(&mSocketAddress, 0, sizeof(mSocketAddress));
    mSocketAddress.sin_family = AF_INET;
    mSocketAddress.sin_addr.s_addr = inet_addr(mHost);
    mSocketAddress.sin_port = htons(mPort);
}

void UdpSocket::Close()
{
    closesocket(mSocket);  
    WSACleanup();
}

void UdpSocket::Send(char* str, size_t length)
{
    size_t result = sendto(mSocket, str, length, 0, 
        (struct sockaddr *) &mSocketAddress, sizeof(mSocketAddress));

    if(result != length)
        perror("sendto() sent incorrect number of bytes");   
}
