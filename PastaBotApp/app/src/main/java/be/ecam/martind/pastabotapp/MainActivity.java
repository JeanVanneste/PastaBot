package be.ecam.martind.pastabotapp;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.DisconnectedBufferOptions;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.io.UnsupportedEncodingException;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final MqttAndroidClient client = getMqttClient(getApplicationContext(),
                getString(R.string.BrockerMQTT), "1");
        final String topic = getString(R.string.topicMQTTCook);

        client.setCallback(new MqttCallbackExtended(){
            @Override
            public void connectComplete(boolean b, String s) {

            }
            @Override
            public void connectionLost(Throwable throwable) {

            }
            @Override
            public void messageArrived(String s, MqttMessage mqttMessage)
                    throws Exception {
                Snackbar snackbar = Snackbar.make(findViewById(R.id.i_time), new String(mqttMessage.getPayload()), Snackbar.LENGTH_LONG);
                snackbar.show();
                publishMessage (client, "=", 1, topic);


            }
            @Override
            public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken) {
                /*
                try{
                    unSubscribe(client, getString(R.string.topicMQTTresp));
                }
                catch (MqttException e){
                    Snackbar snackbar = Snackbar.make(findViewById(R.id.i_time),
                            "MQTT Error", Snackbar.LENGTH_LONG);
                    snackbar.show();
                }
                */
            }

        });


        final Button sendButton = findViewById(R.id.send_button);
        sendButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                try{
                    subscribe(client,  getString(R.string.topicMQTTresp), 1);


                    @NonNull String time = ((EditText)findViewById(R.id.i_time)).getText()
                            .toString();
                    System.out.println(time);

                    if (time.isEmpty()){
                        time = "5";
                    }
                    publishMessage(client, time, 1, topic);
                    Snackbar snackbar = Snackbar.make(v, "Command made, time to cook : "+time+
                            "min", Snackbar.LENGTH_LONG);
                    snackbar.show();
                }
                catch (MqttException e ){
                    Snackbar snackbar = Snackbar.make(v, "MQTT Error", Snackbar.LENGTH_LONG);
                    snackbar.show();
                }
                catch (UnsupportedEncodingException e){
                    Snackbar snackbar = Snackbar.make(v, "Encoding Error",
                            Snackbar.LENGTH_LONG);
                    snackbar.show();
                }
            }
        });


    }

    private MqttConnectOptions getMqttConnectionOption() {
        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setCleanSession(false);
        mqttConnectOptions.setAutomaticReconnect(true);
        return mqttConnectOptions;
    }
    private DisconnectedBufferOptions getDisconnectedBufferOptions() {
        DisconnectedBufferOptions disconnectedBufferOptions = new DisconnectedBufferOptions();
        disconnectedBufferOptions.setBufferEnabled(true);
        disconnectedBufferOptions.setBufferSize(100);
        disconnectedBufferOptions.setPersistBuffer(true);
        disconnectedBufferOptions.setDeleteOldestMessages(false);
        return disconnectedBufferOptions;
    }

    public MqttAndroidClient getMqttClient(Context context, String brokerUrl, String clientId) {
        final MqttAndroidClient mqttAndroidClient = new MqttAndroidClient(context, brokerUrl,
                clientId);
        try {
            IMqttToken token = mqttAndroidClient.connect(getMqttConnectionOption());
            token.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    mqttAndroidClient.setBufferOpts(getDisconnectedBufferOptions());
                    System.out.println("Success connection");
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    System.out.println("Failed connection "+ exception.toString());
                }
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }
        return mqttAndroidClient;
    }

    public void publishMessage(@NonNull MqttAndroidClient client,
                               @NonNull String msg, int qos, @NonNull String topic)
            throws MqttException, UnsupportedEncodingException {
        byte[] encodedPayload = new byte[0];
        encodedPayload = msg.getBytes(StandardCharsets.UTF_8);
        MqttMessage message = new MqttMessage(encodedPayload);
        message.setId(5866);
        message.setRetained(true);
        message.setQos(qos);
        client.publish(topic, message);
    }


    public void subscribe(@NonNull MqttAndroidClient client,
                          @NonNull final String topic, int qos) throws MqttException {
        IMqttToken token = client.subscribe(topic, qos);
        token.setActionCallback(new IMqttActionListener() {

            @Override
            public void onSuccess(IMqttToken iMqttToken) {
                System.out.println("Subscribe Successfully " + topic);
            }

            @Override
            public void onFailure(IMqttToken iMqttToken, Throwable throwable) {
                System.out.println("Subscribe Failed " + topic);
            }
        });
    }

    public void unSubscribe(@NonNull MqttAndroidClient client,
                            @NonNull final String topic) throws MqttException {

        IMqttToken token = client.unsubscribe(topic);
        token.setActionCallback(new IMqttActionListener() {
            @Override
            public void onSuccess(IMqttToken iMqttToken) {
                System.out.println("UnSubscribe Successfully " + topic);
            }

            @Override
            public void onFailure(IMqttToken iMqttToken, Throwable throwable) {
                System.out.println("UnSubscribe Failed " + topic);
            }
        });
    }
}


