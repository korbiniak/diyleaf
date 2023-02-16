import { Color } from 'react-color'

export interface DiyleafFadeColorMode {
  color1: Color;
  color2: Color;
}

export interface DiyleafSingleColorMode {
  color: Color;
}

export interface DiyleafState {
  mode: DiyleafSingleColorMode
}

export interface LightState {
  led_on: boolean;
}

export interface LightMqttSettings {
  unique_id: string;
  name: string;
  mqtt_path: string;
}
