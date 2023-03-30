/* global chrome */

import { Bridge } from '../bridge.mjs'

class EdgeBridge extends Bridge {
  postMessage (message) {
    chrome.webview.postMessage(JSON.stringify(message))
  }
}

globalThis.bridge = new EdgeBridge()
