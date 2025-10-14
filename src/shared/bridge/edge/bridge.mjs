import { Bridge } from '../bridge.mjs'

class EdgeBridge extends Bridge {
  constructor() {
    super()

    globalThis.chrome.webview.addEventListener('message', (event) => {
      this.dispatchMessage(event.data)
    })
  }

  postMessage(message) {
    globalThis.chrome.webview.postMessage(JSON.stringify(message))
  }
}

globalThis.bridge = new EdgeBridge()
