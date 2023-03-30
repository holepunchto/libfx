/* global chrome */

import { Bridge } from '../bridge.mjs'

class EdgeBridge extends Bridge {
  constructor () {
    super()

    chrome.webview.addEventListener('message', (event) => {
      this.dispatchMessage(event.data)
    })
  }

  postMessage (message) {
    chrome.webview.postMessage(JSON.stringify(message))
  }
}

globalThis.bridge = new EdgeBridge()
