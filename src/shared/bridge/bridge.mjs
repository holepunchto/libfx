class MessageEvent extends Event {
  constructor (data, opts) {
    super('message', opts)

    this.data = clone(data)
  }
}

export class Bridge extends EventTarget {
  dispatchMessage (message) {
    return this.dispatchEvent(new MessageEvent(message))
  }
}

function clone (value) {
  return JSON.parse(JSON.stringify(value))
}
