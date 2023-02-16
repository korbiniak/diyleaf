import React, { FC } from 'react';
import { Navigate, Route, Routes } from 'react-router-dom';

import { Tab } from '@mui/material';

import { RouterTabs, useRouterTab, useLayoutTitle } from '../components';

import DemoInformation from './DemoInformation';
import LightStateRestForm from './LightStateRestForm';
import LightMqttSettingsForm from './LightMqttSettingsForm';
import LightStateWebSocketForm from './LightStateWebSocketForm';
import Diyleaf from './Diyleaf';

const DemoProject: FC = () => {
  useLayoutTitle("DiyLeaf");
  const { routerTab } = useRouterTab();

  return (
    <>
      <RouterTabs value={routerTab}>
        <Tab value="information" label="Information" />
        <Tab value="rest" label="REST Example" />
        <Tab value="socket" label="WebSocket Example" />
        <Tab value="mqtt" label="MQTT Settings" />
        <Tab value="diyleaf" label="Diyleaf" />
      </RouterTabs>
      <Routes>
        <Route path="information" element={<DemoInformation />} />
        <Route path="rest" element={<LightStateRestForm />} />
        <Route path="mqtt" element={<LightMqttSettingsForm />} />
        <Route path="socket" element={<LightStateWebSocketForm />} />
        <Route path="diyleaf" element={<Diyleaf />} />
        <Route path="/*" element={<Navigate replace to="information" />} />
      </Routes>
    </>
  );
};

export default DemoProject;
