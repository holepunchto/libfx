/* global webkit */

import { Bridge } from '../bridge.mjs'

class DarwinBridge extends Bridge {
  postMessage (message) {
    webkit.messageHandlers.bridge.postMessage(JSON.stringify(message))
  }
}

globalThis.bridge = new DarwinBridge()
