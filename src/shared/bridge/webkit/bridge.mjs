/* global webkit */

import { Bridge } from '../bridge.mjs'

class WebKitBridge extends Bridge {
  postMessage(message) {
    webkit.messageHandlers.bridge.postMessage(JSON.stringify(message))
  }
}

globalThis.bridge = new WebKitBridge()
