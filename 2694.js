class EventEmitter {

    constructor() {
        // Store event names and their callbacks
        this.events = new Map();
    }

    
    subscribe(eventName, callback) {

        // If event doesn't exist, create an empty array
        if (!this.events.has(eventName)) {
            this.events.set(eventName, []);
        }

        // Add callback to event
        this.events.get(eventName).push(callback);

        return {
            unsubscribe: () => {

                const callbacks = this.events.get(eventName);

                // Find callback index
                const index = callbacks.indexOf(callback);

                // Remove callback
                if (index !== -1) {
                    callbacks.splice(index, 1);
                }

                return undefined;
            }
        };
    }

    emit(eventName, args = []) {

        // No subscribers for this event
        if (!this.events.has(eventName)) {
            return [];
        }

        const callbacks = this.events.get(eventName);
        const results = [];

        // Execute callbacks in subscription order
        for (const callback of callbacks) {
            results.push(callback(...args));
        }

        return results;
    }
}

