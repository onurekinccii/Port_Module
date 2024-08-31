import 'dart:ffi';
import 'dart:io';
import 'package:ffi/ffi.dart';

typedef IsPortOpenC = Int32 Function(Pointer<Utf8> ip, Int32 port);
typedef IsPortOpenDart = int Function(Pointer<Utf8> ip, int port);

void main() {
  final DynamicLibrary portScannerLib = DynamicLibrary.open('port_scanner.dll');
  final IsPortOpenDart isPortOpen = portScannerLib
      .lookupFunction<IsPortOpenC, IsPortOpenDart>('is_port_open');
  final ip = '127.0.0.1'.toNativeUtf8();
  final port = 80;
  final result = isPortOpen(ip, port);

  print('Port $port is ${result == 1 ? 'open' : 'closed'}');

  calloc.free(ip);
}
