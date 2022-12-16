class MessageEvent extends Event {
  constructor (data, opts) {
    super('message', opts)

    this.data = data
  }
}

export class Bridge extends EventTarget {
  dispatchMessage (message) {
    return this.dispatchEvent(new MessageEvent(message))
  }
}
