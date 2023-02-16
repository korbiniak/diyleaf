import { FC, useState } from 'react';

import { WEB_SOCKET_ROOT } from '../api/endpoints';
import { FormLoader, MessageBox, SectionContent } from '../components';
import { updateColorValue, useWs } from '../utils';

import { DiyleafState } from './types';

import { RGBColor, HuePicker } from 'react-color';


export const DIYLEAF_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "diyleafState";

const Diyleaf: FC = () => {
  const { connected, updateData, data } = useWs<DiyleafState>(DIYLEAF_SETTINGS_WEBSOCKET_URL, 1);

  const updateFormValue = updateColorValue(updateData);

  const initialColor: RGBColor = {r: 0xff, g: 0xff, b: 0xff};
  const [color, setColor] = useState(initialColor);

  const content = () => {
    if (!connected || !data) {
      return (<FormLoader message="Connecting to WebSocket…" />);
    }
    return (
      <>
        <MessageBox
          level="info"
          message="The switch below controls the LED via the WebSocket. It will automatically update whenever the LED state changes."
          my={2}
        />
        <HuePicker 
          color={color}
          onChange={(newColor, e) => {
            updateFormValue(newColor.rgb);
            setColor(newColor.rgb);
            console.log(data);
            console.log(newColor.rgb);
            console.log(e.target);
          }
        }/>
      </>
    );
  };

  return (
    <SectionContent title='WebSocket Example' titleGutter>
      {content()}
    </SectionContent>
  );
};

export default Diyleaf;
