import 'package:flutter/material.dart';
import 'package:wifi/wifi.dart';
import 'package:nfc_in_flutter/nfc_in_flutter.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
        visualDensity: VisualDensity.adaptivePlatformDensity,
      ),
      home: MyHomePage(title: 'Wifi Connect App'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);
  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  String _ssid;
  String _passwd;

  nfcEntry() {
    nfcRead();
    wifiConnect(_ssid, _passwd);
  }

  wifiConnect(String ssid, String passwd) async {
    var wifiConnectStatus = await Wifi.connection(ssid, passwd);
  }

  nfcRead() async {
    NDEFMessage message = await NFC.readNDEF(once: true).first;

    // analyse
    List<String> npList = message.payload.split(',');
    _ssid = npList[0];
    _passwd = npList[1];
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            RaisedButton(
              child: Text('nfc'),
              onPressed: nfcEntry,
            ),
          ],
        ),
      ),
    );
  }
}
