/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//yunhe
#define BILLION 1000000000L
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;
using helloworld::intVal;
using helloworld::doubleVal;
using helloworld::circleVal;

circleVal MakeCircle(int center, double r, bool color) {
  circleVal c;
  c.set_center(center);
  c.set_r(r);
  c.set_color(color);
  return c;
}

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  int SayHello(const int user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    std::cout << "** yunhe: rpc start\n";
    uint64_t diff;
    struct timespec start0, end0;
    clock_gettime(CLOCK_MONOTONIC, &start0);

    Status status = stub_->SayHello(&context, request, &reply);

    clock_gettime(CLOCK_MONOTONIC, &end0);
    diff = BILLION * (end0.tv_sec - start0.tv_sec) + end0.tv_nsec - start0.tv_nsec;
    std::cout << "@@ diff = ";
    std::cout << diff;
    std::cout << " @@\n";

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -2;
    }
  }

  int incOne(const int inInt) {
    intVal request;
    request.set_val(inInt);

    intVal reply;

    ClientContext context;

    // The actual RPC.
//    std::cout << "** yunhe: rpc start\n";
    uint64_t diff;
    struct timespec start0, end0;
    clock_gettime(CLOCK_MONOTONIC, &start0);

    Status status = stub_->incOne(&context, request, &reply);

    clock_gettime(CLOCK_MONOTONIC, &end0);
    diff = BILLION * (end0.tv_sec - start0.tv_sec) + end0.tv_nsec - start0.tv_nsec;
    std::cout << "@@ int rtt diff = ";
    std::cout << diff;
    std::cout << " @@\n";

    // Act upon its status.
    if (status.ok()) {
      return reply.val();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -3;
    }
  }

  double half(const double inDouble) {
    doubleVal request;
    request.set_val(inDouble);

    doubleVal reply;

    ClientContext context;

    // The actual RPC.
//    std::cout << "** yunhe: rpc start\n";
    uint64_t diff;
    struct timespec start0, end0;
    clock_gettime(CLOCK_MONOTONIC, &start0);

    Status status = stub_->half(&context, request, &reply);

    clock_gettime(CLOCK_MONOTONIC, &end0);
    diff = BILLION * (end0.tv_sec - start0.tv_sec) + end0.tv_nsec - start0.tv_nsec;
    std::cout << "@@ double rtt diff = ";
    std::cout << diff;
    std::cout << " @@\n";

    // Act upon its status.
    if (status.ok()) {
      return reply.val();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -4.0;
    }
  }

  double expand(const circleVal inCircle) {
    circleVal request;
    //TODO fix, used passed in parameter
    request.set_center(1);
    request.set_r(2.0);
    request.set_color(true);

    circleVal reply;

    ClientContext context;

    // The actual RPC.
//    std::cout << "** yunhe: rpc start\n";
    uint64_t diff;
    struct timespec start0, end0;
    clock_gettime(CLOCK_MONOTONIC, &start0);

    Status status = stub_->expand(&context, request, &reply);

    clock_gettime(CLOCK_MONOTONIC, &end0);
    diff = BILLION * (end0.tv_sec - start0.tv_sec) + end0.tv_nsec - start0.tv_nsec;
    std::cout << "@@ circle rtt diff = ";
    std::cout << diff;
    std::cout << " @@\n";

    // Act upon its status.
    if (status.ok()) {
      return reply.r();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -5.0;
    }
  }
 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  GreeterClient greeter(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
//  int power = atoi(argv[1]); //string len = 2^power
//  int i = 0;
//  std::string user("a");
//  for(i = 0; i < power; i++){
//    user.append(user);
//  }
  //std::cout << argc;
  //std::cout << argv[1];
//  int user = 1;
//  int reply = greeter.SayHello(user);
  std::cout << "experiment 1 start" << std::endl;
  int inInt = 2;
  int outInt = greeter.incOne(inInt);
  
  int inInt1 = 4;
  int outInt1 = greeter.incOne(inInt1);
  
  double inDouble = 3.5;
  double outDouble = greeter.half(inDouble);

  circleVal inCircle = MakeCircle(0, 2.0, true);
  double outCircle = greeter.expand(inCircle);
//  std::cout << "** power = ";
//  std::cout << power;
//  std::cout << " **\n";
//  std::cout << "Greeter received: " << reply << std::endl;
  std::cout << "outInt =  2 + 1 = " << outInt << std::endl;
  std::cout << "outInt =  5 + 1 = " << outInt1 << std::endl;
  std::cout << "outDouble = 3.5/2 = " << outDouble << std::endl;
  std::cout << "Circle radius from 2.0 to: " << outCircle << std::endl;
  return 0;
}
